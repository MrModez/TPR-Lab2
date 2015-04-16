// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "KRLab.h"
#define DEBUG			ShowMessage
#define INT				StrToInt
#define STR				IntToStr
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

	KRProfile Prof1 = KRProfile("Prof1", Crits);
	int C[] = {25, 85, 2};
	Prof1.SetCrits(C);
	Profiles.AddProfile(Prof1);

	KRProfile Prof2 = KRProfile("Prof2", Crits);
	Prof2.ChangeCrit(0, 35);
	Prof2.ChangeCrit(1, 52);
	Prof2.ChangeCrit(2, 3);
	Profiles.AddProfile(Prof2);

	Profiles.AddProfile(KRProfile("Prof3", Crits));
	Profiles.ChangeProfile(2, 0, 60);
	Profiles.ChangeProfile(2, 1, 100);
	Profiles.ChangeProfile(2, 2, 1);

	Profiles.AddWorst(KRProfile("Worst", Crits));
	Profiles.ChangeWorst(0, 20);
	Profiles.ChangeWorst(1, 0);
	Profiles.ChangeWorst(2, 10);
	Profiles.AddBest(KRProfile("Best", Crits));
	Profiles.ChangeBest(0, 60);
	Profiles.ChangeBest(1, 100);
	Profiles.ChangeBest(2, 1);
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::ShowButClick(TObject *Sender) {
	// qwe
	StringGrid->RowCount = Profiles.GetSize() + 3;
	StringGrid->ColCount = Profiles.Crits.GetSize() + 1;

	for (int i = 0; i < Profiles.GetSize(); i++) {
		StringGrid->Cells[0][i + 1] = Profiles.GetByIndex(i).Name;
		StringGrid->Cells[0][Profiles.GetSize() + 1] = Profiles.GetBest().Name;
		StringGrid->Cells[0][Profiles.GetSize() + 2] = Profiles.GetWorst().Name;
		for (int j = 0; j < Profiles.Crits.GetSize(); j++) {
			StringGrid->Cells[j + 1][0] = Profiles.Crits.GetByIndex(j).Name;
			StringGrid->Cells[j + 1][i + 1] = STR(Profiles.GetByIndex(i).GetValue(j));
			StringGrid->Cells[j + 1][Profiles.GetSize() + 2] = STR(Profiles.GetBest().GetValue(j));
			StringGrid->Cells[j + 1][Profiles.GetSize() + 1] = STR(Profiles.GetWorst().GetValue(j));
		}
	}
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::GraphButClick(TObject *Sender) {
	///
	int i = IndexSpin->Value;
	int Worst = Profiles.GetWorst().GetValue(i);
	int Best = Profiles.GetBest().GetValue(i);
	// DEBUG((int)Profiles.Crits.GetByIndex(i).dec);
	if (Profiles.Crits.GetByIndex(i).dec) {
		Best = Profiles.GetWorst().GetValue(i);
		Worst = Profiles.GetBest().GetValue(i);
	}
	A25Spin->Value = (Worst + (Worst + Best) / 2.0) / 2.0;
	A50Spin->Value = (Worst + Best) / 2.0;
	A75Spin->Value = (Best + (Worst + Best) / 2.0) / 2.0;
	PaintBox1->Refresh();
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::PaintBox1Paint(TObject *Sender) {
	int i = IndexSpin->Value;
	bool dec = Profiles.Crits.GetByIndex(i).dec;
	int iBest = Profiles.GetBest().GetValue(i);
	int iWorst = Profiles.GetWorst().GetValue(i);
	if (dec) {
		iBest = Profiles.GetWorst().GetValue(i);
		iWorst = Profiles.GetBest().GetValue(i);
	}
	int iA25 = A25Spin->Value;
	int iA50 = A50Spin->Value;
	int iA75 = A75Spin->Value;
	///
	TDirect2DCanvas* Canvas;
	Canvas = new TDirect2DCanvas(PaintBox1->Canvas, PaintBox1->ClientRect);
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
		int Y0 = 0 * 2;
		int Y25 = 25 * 2;
		int Y50 = 50 * 2;
		int Y75 = 75 * 2;
		int Y100 = 100 * 2;
		if (dec) {
			Y0 = 100 * 2;
			Y75 = 25 * 2;
			Y50 = 50 * 2;
			Y25 = 75 * 2;
			Y100 = 0 * 2;
		}
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
		Canvas->CIRCLE(oX + 0, oY - Y0);
		Canvas->CIRCLE(oX + A25, oY - Y25);
		Canvas->CIRCLE(oX + A50, oY - Y50);
		Canvas->CIRCLE(oX + A75, oY - Y75);
		Canvas->CIRCLE(oX + W, oY - Y100);

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
void __fastcall TMainForm::A25SpinChange(TObject *Sender) {
	PaintBox1->Refresh();
}
// ---------------------------------------------------------------------------
