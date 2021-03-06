// ---------------------------------------------------------------------------

#ifndef KRLabH
#define KRLabH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Samples.Spin.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ComCtrls.hpp>
#include <vector>
#include <algorithm>
#include <Direct2D.hpp>
#include "KRCrit.h"
#include "KRCritSys.h"
#include "KRProfile.h"
#include "KRProfileSys.h"

// ---------------------------------------------------------------------------
class TMainForm : public TForm {
__published: // IDE-managed Components

	TStringGrid *StringGrid;
	TButton *ShowBut;
	TPaintBox *GraphPaintBox;
	TSpinEdit *A25Spin;
	TSpinEdit *A50Spin;
	TSpinEdit *A75Spin;
	TStringGrid *AStringGrid;
	TButton *SubBut;
	TSpinEdit *MIndexSpin0;
	TLabel *MLabel1;
	TLabel *MLabel2;
	TSpinEdit *MValueSpin;
	TLabel *QLabel;
	TLabel *VLabel;
	TButton *CalcBut;
	TStringGrid *RStringGrid;
	TButton *StartBut;
	TButton *LoadBut;
	TOpenDialog *DatOpenDialog;
	TUpDown *IndexSpin;
	TLabel *GLabel;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TUpDown *MIndexSpin;
	TLabel *MLabel;
	TLabel *Label4;
	TPanel *CoverPanel;
	TLabel *Label5;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ShowButClick(TObject *Sender);
	void __fastcall GraphPaintBoxPaint(TObject *Sender);
	void __fastcall A25SpinChange(TObject *Sender);
	void __fastcall A50SpinChange(TObject *Sender);
	void __fastcall A75SpinChange(TObject *Sender);
	void __fastcall SubButClick(TObject *Sender);
	void __fastcall MIndexSpin0Change(TObject *Sender);
	void __fastcall GraphPaintBoxClick(TObject *Sender);
	void __fastcall MValueSpinChange(TObject *Sender);
	void __fastcall CalcButClick(TObject *Sender);
	void __fastcall StartButClick(TObject *Sender);
	void __fastcall LoadButClick(TObject *Sender);
	void __fastcall IndexSpinMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall AStringGridKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall RStringGridClick(TObject *Sender);
	void __fastcall MIndexSpinMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall StringGridKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall CoverPanelClick(TObject *Sender);








private: // User declarations
		;

public: // User declarations

	KRCritSys Crits;
	KRProfileSys Profiles;

	__fastcall TMainForm(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
// ---------------------------------------------------------------------------
#endif
