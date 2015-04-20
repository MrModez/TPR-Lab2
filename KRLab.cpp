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
	///

}

// --------------------------------------------------------------------------
void __fastcall TMainForm::StartButClick(TObject *Sender) {
	Crits = KRCritSys();
	Crits.AddCrit(KRCrit("Время решения", 1));
	Crits.AddCrit(KRCrit("Точность", 0));
	Crits.AddCrit(KRCrit("Устойчивость", 0));
	Crits.AddCrit(KRCrit("Память", 1));

	KRProfile* Worst = new KRProfile("Худш", Crits);
	int CW[] = {500, 20, 0, 256};
	Worst->SetCrits(CW);

	KRProfile* Best = new KRProfile("Лучш", Crits);
	int CB[] = {1, 100, 1, 2};
	Best->SetCrits(CB);

	Profiles = KRProfileSys(Worst, Best, Crits);

	KRProfile* Prof1 = new KRProfile("МВГ", Crits);
	int C[] = {40, 100, 1, 16};
	Prof1->SetCrits(C);
	Profiles.AddProfile(Prof1);

	KRProfile* Prof2 = new KRProfile("ГА", Crits);
	int C2[] = {8, 85, 1, 32};
	Prof2->SetCrits(C2);
	Profiles.AddProfile(Prof2);

	KRProfile* Prof3 = new KRProfile("МБС", Crits);
	int C3[] = {20, 70, 0, 64};
	Prof3->SetCrits(C3);
	Profiles.AddProfile(Prof3);

	KRProfile* Prof4 = new KRProfile("Пере", Crits);
	int C4[] = {120, 100, 1, 128};
	Prof4->SetCrits(C4);
	Profiles.AddProfile(Prof4);

	ShowButClick(this);
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::LoadButClick(TObject *Sender) {
	if (DatOpenDialog->Execute()) {
		TStringList* Dat = new TStringList;
		Dat->LoadFromFile(DatOpenDialog->FileName);
		Profiles = KRProfileSys(Dat);
		delete Dat;
	}
	ShowButClick(this);
	SubButClick(this);
	LoadBut->Visible = false;
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
	IndexSpin->Min = 0;
	IndexSpin->Max = Profiles.GetSize() - 1;

	// AStringGrid
	AStringGrid->RowCount = Profiles.Crits.GetSize() + 1;
	AStringGrid->ColCount = 2;

	for (int j = 0; j < Profiles.Crits.GetSize(); j++) {
		AStringGrid->Cells[0][j + 1] = Profiles.Crits.GetByIndex(j).Name;
		AStringGrid->Cells[1][j + 1] = Profiles.Crits.GetPriority(j);
	}

	GraphPaintBox->Visible = true;
	GraphPaintBoxClick(this);
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::GraphPaintBoxPaint(TObject * Sender) {
	int i = IndexSpin->Position;
	bool dec = Profiles.Crits.GetByIndex(i).dec;
	int iBest = Profiles.GetBest()->GetValue(i);
	int iWorst = Profiles.GetWorst()->GetValue(i);
	if (dec) {
		iBest = Profiles.GetWorst()->GetValue(i);
		iWorst = Profiles.GetBest()->GetValue(i);
	}
	int iA25 = Profiles.GetSpecial(A_25)->GetValue(i);
	int iA50 = Profiles.GetSpecial(A_50)->GetValue(i);
	int iA75 = Profiles.GetSpecial(A_75)->GetValue(i);
	String sA25 = STRF(Profiles.GetSpecial(A_25)->GetCoeff(i));

	///
	TDirect2DCanvas* Canvas;
	Canvas = new TDirect2DCanvas(GraphPaintBox->Canvas, GraphPaintBox->ClientRect);
	Canvas->RenderTarget->SetAntialiasMode(D2D1_ANTIALIAS_MODE_FORCE_DWORD);
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
	int i = IndexSpin->Position;
	A25Spin->Value = Profiles.GetSpecial(A_25)->GetValue(i);
	A50Spin->Value = Profiles.GetSpecial(A_50)->GetValue(i);
	A75Spin->Value = Profiles.GetSpecial(A_75)->GetValue(i);
	GLabel->Caption = Profiles.Crits.GetByIndex(i).Name;
	GraphPaintBox->Refresh();
}

// ---------------------------------------------------------------------------

void __fastcall TMainForm::A25SpinChange(TObject * Sender) {
	int i = IndexSpin->Position;
	Profiles.ChangeSpecial(A_25, i, A25Spin->Value);
	GraphPaintBox->Refresh();
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::A50SpinChange(TObject * Sender) {
	int i = IndexSpin->Position;
	Profiles.ChangeSpecial(A_50, i, A50Spin->Value);
	GraphPaintBox->Refresh();
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::A75SpinChange(TObject * Sender) {
	int i = IndexSpin->Position;
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
			}
		}
	}
	Profiles.Crits.SetPrority(Priority);

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
	String Str = "";
	Profiles.SetEQCoeffs();
	Profiles.SetLambdas();

	Str = "";
	for (int i = 0; i < Profiles.Crits.GetSize(); i++) {
		Str += STRF(Profiles.Crits.GetLambda(i)) + "\n";
	}
	VLabel->Caption = Str;

	RStringGrid->RowCount = Profiles.GetSize() + 1;
	RStringGrid->ColCount = 2;

	for (int i = 0; i < Profiles.GetSize(); i++) {
		RStringGrid->Cells[0][i + 1] = Profiles.GetByIndex(i)->Name;
		RStringGrid->Cells[1][i + 1] = STRF(Profiles.ResultValue(i));
	}
}

// ---------------------------------------------------------------------------

void __fastcall TMainForm::IndexSpinMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
	int X, int Y) {
	GraphPaintBoxClick(this);
}
// ---------------------------------------------------------------------------
