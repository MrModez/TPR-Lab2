// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "KRLab.h"
#define DEBUG			ShowMessage
#define STR(INT) 			IntToStr((int)INT)
#define INT(STR) 			StrToInt(STR)
#define FLT(STR) 			StrToFloat(STR)
#define STRF(STR) 			FloatToStrF(STR, ffGeneral, 4, 2)
#define COS 			cos
#define SIN 			sin
#define R	 			3
#define CIRCLE(X, Y)	Ellipse(X - R, Y - R + 1, X + R, Y + R + 1)
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;

// ---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner) : TForm(Owner) {
	MainForm->ControlStyle << csOpaque;
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject *Sender) {
	Crits = KRCritSys();
	Crits.AddCrit(KRCrit("Crit1", 0));
	Crits.AddCrit(KRCrit("Crit2", 0));
	Crits.AddCrit(KRCrit("Crit3", 1));

	Profiles = KRProfileSys(Crits);

	KRProfile* Prof1 = new KRProfile("Prof1", Crits);
	int C[] = {25, 85, 2};
	Prof1->SetCrits(C);
	Profiles.AddProfile(Prof1);

	KRProfile* Prof2 = new KRProfile("Prof2", Crits);
	Prof2->ChangeCrit(0, 35);
	Prof2->ChangeCrit(1, 52);
	Prof2->ChangeCrit(2, 3);
	Profiles.AddProfile(Prof2);

	Profiles.AddProfile(new KRProfile("Prof3", Crits));
	Profiles.ChangeProfile(2, 0, 60);
	Profiles.ChangeProfile(2, 1, 100);
	Profiles.ChangeProfile(2, 2, 1);

	Profiles.AddWorst(new KRProfile("Worst", Crits));
	Profiles.ChangeWorst(0, 20);
	Profiles.ChangeWorst(1, 0);
	Profiles.ChangeWorst(2, 10);
	Profiles.AddBest(new KRProfile("Best", Crits));
	Profiles.ChangeBest(0, 60);
	Profiles.ChangeBest(1, 100);
	Profiles.ChangeBest(2, 1);

	// KRProfile A25 = KRProfile("A25", Crits);
	// A25.ChangeCoeff()
	Profiles.AddSpecial(A_25, new KRProfile("A25", Crits));
	Profiles.AddSpecial(A_50, new KRProfile("A50", Crits));
	Profiles.AddSpecial(A_75, new KRProfile("A75", Crits));
	Profiles.AddSpecial(A_EQ, new KRProfile("AEQ", Crits));
	Profiles.GetSpecial(A_WORST)->ChangeCoeff(0.0);
	Profiles.GetSpecial(A_25)->ChangeCoeff(0.25);
	Profiles.GetSpecial(A_50)->ChangeCoeff(0.50);
	Profiles.GetSpecial(A_75)->ChangeCoeff(0.75);
	Profiles.GetSpecial(A_BEST)->ChangeCoeff(1.0);
	Profiles.GetSpecial(A_EQ)->ChangeCoeff(0);

	for (int i = 0; i < Crits.GetSize(); i++) {
		int Worst = Profiles.GetWorst()->GetValue(i);
		int Best = Profiles.GetBest()->GetValue(i);
		if (Profiles.Crits.GetByIndex(i).dec) {
			Worst = Profiles.GetWorst()->GetValue(i);
			Best = Profiles.GetBest()->GetValue(i);
		}
		// Profiles.GetSpecial(A_25)->ChangeCrit(i, (Worst + (Worst + Best) / 2.0) / 2.0);
		Profiles.ChangeSpecial(A_25, i, (Worst + (Worst + Best) / 2.0) / 2.0);
		Profiles.ChangeSpecial(A_50, i, (Worst + Best) / 2.0);
		Profiles.ChangeSpecial(A_75, i, (Best + (Worst + Best) / 2.0) / 2.0);
		Profiles.ChangeSpecial(A_EQ, i, (Worst + Best) / 2.0);
		if (Profiles.Crits.GetByIndex(i).dec) {
			Profiles.ChangeSpecial(A_25, i, (Worst + (Worst + Best) / 2.0) / 2.0);
			Profiles.ChangeSpecial(A_50, i, (Worst + Best) / 2.0);
			Profiles.ChangeSpecial(A_75, i, (Best + (Worst + Best) / 2.0) / 2.0);
			Profiles.ChangeSpecial(A_EQ, i, (Worst + Best) / 2.0);
		}
	}
	// A25Spin->Value = (Worst + (Worst + Best) / 2.0) / 2.0;
	// A50Spin->Value = (Worst + Best) / 2.0;
	// A75Spin->Value = (Best + (Worst + Best) / 2.0) / 2.0;
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::ShowButClick(TObject *Sender) {
	// qwe
	StringGrid->RowCount = Profiles.GetSize() + 3;
	StringGrid->ColCount = Profiles.Crits.GetSize() + 1;

	for (int i = 0; i < Profiles.GetSize(); i++) {
		StringGrid->Cells[0][i + 1] = Profiles.GetByIndex(i)->Name; // TEST
		StringGrid->Cells[0][Profiles.GetSize() + 2] = Profiles.GetBest()->Name;
		StringGrid->Cells[0][Profiles.GetSize() + 1] = Profiles.GetWorst()->Name;
		for (int j = 0; j < Profiles.Crits.GetSize(); j++) {
			StringGrid->Cells[j + 1][0] = Profiles.Crits.GetByIndex(j).Name;
			StringGrid->Cells[j + 1][i + 1] = STR(Profiles.GetByIndex(i)->GetValue(j));
			StringGrid->Cells[j + 1][Profiles.GetSize() + 2] = STR(Profiles.GetBest()->GetValue(j));
			StringGrid->Cells[j + 1][Profiles.GetSize() + 1] =
				STR(Profiles.GetWorst()->GetValue(j));
		}
	}

	///
	IndexSpin->MinValue = 0;
	IndexSpin->MaxValue = Profiles.GetSize() - 1;

	// AStringGrid
	AStringGrid->RowCount = Profiles.Crits.GetSize() + 1;
	AStringGrid->ColCount = 2;

	for (int j = 0; j < Profiles.Crits.GetSize(); j++) {
		AStringGrid->Cells[0][j + 1] = Profiles.Crits.GetByIndex(j).Name;
	}

	GraphPaintBoxClick(this);
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::GraphPaintBoxPaint(TObject * Sender) {
	int i = IndexSpin->Value;
	bool dec = Profiles.Crits.GetByIndex(i).dec;
	int iBest = Profiles.GetBest()->GetValue(i);
	int iWorst = Profiles.GetWorst()->GetValue(i);
	if (dec) {
		iBest = Profiles.GetWorst()->GetValue(i);
		iWorst = Profiles.GetBest()->GetValue(i);
	}
	int iA25 = Profiles.GetSpecial(A_25)->GetValue(i);
	String sA25 = STRF(Profiles.GetSpecial(A_25)->GetCoeff(i));
	int iA50 = Profiles.GetSpecial(A_50)->GetValue(i);
	int iA75 = Profiles.GetSpecial(A_75)->GetValue(i);

	///
	TDirect2DCanvas* Canvas;
	Canvas = new TDirect2DCanvas(GraphPaintBox->Canvas, GraphPaintBox->ClientRect);
	// if (AACheck->Checked)
	Canvas->RenderTarget->SetAntialiasMode(D2D1_ANTIALIAS_MODE_FORCE_DWORD);
	// else
	// Canvas->RenderTarget->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);
	Canvas->BeginDraw();
	try {
		Canvas->Brush->Style = bsClear;
		Canvas->Pen->Color = clBlack;
		Canvas->Pen->Style = psSolid;
		Canvas->Pen->Width = 1;
		int Shift = iWorst;
		float Scale = 100.0 / (float)(iBest - Shift);
		int Worst = (iWorst - Shift) * Scale * 2.0;
		int Best = (iBest - Shift) * Scale * 2.0;
		int A25 = (iA25 - Shift) * Scale * 2.0;
		int A50 = (iA50 - Shift) * Scale * 2.0;
		int A75 = (iA75 - Shift) * Scale * 2.0;
		if (dec) {
			Worst = (iBest - Shift) * Scale * 2.0;
			Best = (iWorst - Shift) * Scale * 2.0;
		}
		int Y0 = 0 * 2;
		int Y25 = 25 * 2;
		int Y50 = 50 * 2;
		int Y75 = 75 * 2;
		int Y100 = 100 * 2;

		int oX = 30, oY = 220;
		int W = 200, H = 200;

		Canvas->MoveTo(oX, oY);
		Canvas->LineTo(oX + W + 20, oY);
		Canvas->MoveTo(oX, oY);
		Canvas->LineTo(oX, oY - H - 20);

		Canvas->TextOutW(oX - 10, oY, STR(iWorst));
		Canvas->TextOutW(oX - 10 + A25, oY, STR(iA25));
		Canvas->TextOutW(oX - 10 + A50, oY, STR(iA50));
		Canvas->TextOutW(oX - 10 + A75, oY, STR(iA75));
		Canvas->TextOutW(oX - 10 + W, oY, STR(iBest));

		Canvas->TextOutW(oX - 15, oY - 15, "0");
		Canvas->TextOutW(oX - 30, oY - Y25 - 10, "0.25");
		Canvas->TextOutW(oX - 30, oY - Y50 - 10, "0.50");
		Canvas->TextOutW(oX - 30, oY - Y75 - 10, "0.75");
		Canvas->TextOutW(oX - 30, oY - H - 10, "1.00");

		Canvas->Pen->Color = clBlack;
		Canvas->CIRCLE(oX + Worst, oY - Y0);
		Canvas->CIRCLE(oX + A25, oY - Y25);
		Canvas->CIRCLE(oX + A50, oY - Y50);
		Canvas->CIRCLE(oX + A75, oY - Y75);
		Canvas->CIRCLE(oX + Best, oY - Y100);

		Canvas->Pen->Color = clGray;
		Canvas->Pen->Style = psDash;
		Canvas->MoveTo(oX + A25, oY - Y25);
		Canvas->LineTo(oX + A25, oY - 0);
		Canvas->MoveTo(oX + A25, oY - Y25);
		Canvas->LineTo(oX + 0, oY - Y25);

		Canvas->MoveTo(oX + A50, oY - Y50);
		Canvas->LineTo(oX + A50, oY - 0);
		Canvas->MoveTo(oX + A50, oY - Y50);
		Canvas->LineTo(oX + 0, oY - Y50);

		Canvas->MoveTo(oX + A75, oY - Y75);
		Canvas->LineTo(oX + A75, oY - 0);
		Canvas->MoveTo(oX + A75, oY - Y75);
		Canvas->LineTo(oX + 0, oY - Y75);

		Canvas->MoveTo(oX + Best, oY - Y100);
		Canvas->LineTo(oX + Best, oY - 0);
		Canvas->MoveTo(oX + Best, oY - Y100);
		Canvas->LineTo(oX + 0, oY - Y100);

		Canvas->Pen->Width = 1;
		Canvas->Pen->Color = clBlack;
		Canvas->Pen->Style = psSolid;
		TPoint Poly[] = {
			Point(oX + Worst, oY - Y0), Point(oX + A25, oY - Y25), Point(oX + A50, oY - Y50),
				Point(oX + A75, oY - Y75), Point(oX + Best, oY - Y100)};
		Canvas->Polyline(Poly, 4);
	}
	__finally {
		Canvas->EndDraw();
		Canvas->Free();
	}

}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::GraphPaintBoxClick(TObject *Sender) {
	int i = IndexSpin->Value;
	A25Spin->Value = Profiles.GetSpecial(A_25)->GetValue(i);
	A50Spin->Value = Profiles.GetSpecial(A_50)->GetValue(i);
	A75Spin->Value = Profiles.GetSpecial(A_75)->GetValue(i);
	GraphPaintBox->Refresh();
}

// ---------------------------------------------------------------------------

void __fastcall TMainForm::A25SpinChange(TObject * Sender) {
	int i = IndexSpin->Value;
	Profiles.ChangeSpecial(A_25, i, A25Spin->Value);
	GraphPaintBox->Refresh();
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::A50SpinChange(TObject * Sender) {
	int i = IndexSpin->Value;
	Profiles.ChangeSpecial(A_50, i, A50Spin->Value);
	GraphPaintBox->Refresh();
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::A75SpinChange(TObject * Sender) {
	int i = IndexSpin->Value;
	Profiles.ChangeSpecial(A_75, i, A75Spin->Value);
	GraphPaintBox->Refresh();
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::SubButClick(TObject *Sender) {
	///
	std::vector<int>Priority;
	for (int i = 0; i < Profiles.Crits.GetSize(); i++) {
		for (int j = 0; j < Profiles.Crits.GetSize(); j++) {
			if (AStringGrid->Cells[1][j + 1] == i) {
				Priority.push_back(j);
				break;
			}
		}
	}
	Profiles.Crits.SetPrority(Priority);
	// ShowMessage(Profiles.Crits.GetByIndex(Priority[0]).Name);
	String Str = Profiles.Crits.GetByIndex(Priority[0]).Name;
	for (int i = 1; i < Profiles.Crits.GetSize(); i++) {
		Str += " > " + Profiles.Crits.GetByIndex(Priority[i]).Name;
	}
	QLabel->Caption = Str;

	for (int i = 0; i < Crits.GetSize(); i++) {
		int Worst = Profiles.GetWorst()->GetValue(Priority[0]);
		int Best = Profiles.GetBest()->GetValue(Priority[0]);
		if (Profiles.Crits.GetByIndex(Priority[0]).dec) {
			Best = Profiles.GetWorst()->GetValue(Priority[0]);
			Worst = Profiles.GetBest()->GetValue(Priority[0]);
		}
		Profiles.ChangeSpecial(A_EQ, i, (Worst + Best) / 2.0);
	}

	MIndexSpin->MinValue = 1;
	MIndexSpin->MaxValue = Profiles.Crits.GetSize() - 1;
	MIndexSpin->Value = 1;
	MIndexSpinChange(this);
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::MIndexSpinChange(TObject *Sender) {
	///
	int i = Profiles.Crits.GetPriority(MIndexSpin->Value);
	int j = Profiles.Crits.GetPriority(0);
	if (!Profiles.Crits.GetByIndex(j).dec) {
		MValueSpin->MinValue = Profiles.GetWorst()->GetValue(j);
		MValueSpin->MaxValue = Profiles.GetBest()->GetValue(j);
		MValueSpin->Value = Profiles.GetSpecial(A_EQ)->GetValue(i);
	}
	else {
		MValueSpin->MinValue = Profiles.GetBest()->GetValue(j);
		MValueSpin->MaxValue = Profiles.GetWorst()->GetValue(j);
		MValueSpin->Value = Profiles.GetSpecial(A_EQ)->GetValue(i);
	}
	MValueSpinChange(this);
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::MValueSpinChange(TObject *Sender) {
	int j = MIndexSpin->Value;
	int base = Profiles.Crits.GetPriority(0);
	int index = Profiles.Crits.GetPriority(j);
	Profiles.ChangeSpecial(A_EQ, index, MValueSpin->Value);

	String Str;
	int A1 = base; // 2
	int A2 = index; // 1

	Str = "X" + STR(base) + ": (";
	for (int i = 0; i < Profiles.Crits.GetSize(); i++) {
		if (A1 == i)
			Str += STR(Profiles.GetSpecial(A_EQ)->GetValue(index)) + "?"; // SHIT
		else
			Str += STR(Profiles.GetWorst()->GetValue(i));
		if (i + 1 < Profiles.Crits.GetSize())
			Str += ", ";
		else
			Str += ")";
	}
	MLabel1->Caption = Str;

	Str = "X" + STR(index) + ": (";
	for (int i = 0; i < Profiles.Crits.GetSize(); i++) {
		if (A2 == i)
			Str += STR(Profiles.GetBest()->GetValue(i));
		else
			Str += STR(Profiles.GetWorst()->GetValue(i));
		if (i + 1 < Profiles.Crits.GetSize())
			Str += ", ";
		else
			Str += ")";
	}
	MLabel2->Caption = Str;

	int value = Profiles.GetSpecial(A_EQ)->GetValue(index);
	float Res = Profiles.GraphValue(base, value);
	VLabel->Caption = STRF(Res);
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::CalcButClick(TObject * Sender) {
	///
	std::vector<float>X;
	// X.resize(Profiles.Crits.GetSize());
	std::vector<float>a;

	String Str = "";
	for (int i = 0; i < Profiles.Crits.GetSize(); i++) {
		int base = Profiles.Crits.GetPriority(0);
		int index = Profiles.Crits.GetPriority(i);
		int value = Profiles.GetSpecial(A_EQ)->GetValue(index);
		float res = Profiles.GraphValue(base, value);
		Profiles.GetSpecial(A_EQ)->ChangeCoeff(index, res);

		float Res = Profiles.GetSpecial(A_EQ)->GetCoeff(Profiles.Crits.GetPriority(i));
		Str += STR(i) + ": " + STRF(Res) + "\n";
		a.push_back(Res);
	}
	// DEBUG(Str);

	float sum = 1;
	for (unsigned int i = 1; i < a.size(); i++) {
		sum += a[i];
	}

	X.push_back(1 / sum);
	for (int i = 1; i < Profiles.Crits.GetSize(); i++) {
		X.push_back(X[i] = a[i] * X[0]);
	}

	std::vector<float>L;
	for (int i = 0; i < Profiles.Crits.GetSize(); i++) {
		int index = Profiles.Crits.GetPriority(i);
		L.push_back(X[index]);
	}
	Profiles.Crits.SetLambdas(L);

	Str = "";
	for (int i = 0; i < Profiles.Crits.GetSize(); i++) {
		Str += STRF(Profiles.Crits.GetLambda(i)) + "\n";
	}
	VLabel->Caption = Str;
	// DEBUG(Str);
}

// --------------------------------------------------------------------------
void __fastcall TMainForm::ResButtonClick(TObject *Sender) {
	// float res = Profiles.GraphValue(0, Profiles.GetByIndex(0)->GetValue(0));
	// Profiles.GraphValue(k, Profiles.GetByIndex(i)->GetValue(k));
	// DEBUG(STRF(res));

	// AStringGrid
	RStringGrid->RowCount = Profiles.GetSize() + 1;
	RStringGrid->ColCount = 2;

	for (int i = 0; i < Profiles.GetSize(); i++) {
		RStringGrid->Cells[0][i + 1] = Profiles.GetByIndex(i)->Name;
		RStringGrid->Cells[1][i + 1] = STRF(Profiles.ResultValue(i));
		// DEBUG(STRF(Profiles.ResultValue(i)));
	}
}
// ---------------------------------------------------------------------------
