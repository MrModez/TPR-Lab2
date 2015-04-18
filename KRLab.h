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
#include <vector>
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
	TSpinEdit *IndexSpin;
	TStringGrid *AStringGrid;
	TButton *SubBut;
	TSpinEdit *MIndexSpin;
	TLabel *MLabel1;
	TLabel *MLabel2;
	TSpinEdit *MValueSpin;
	TLabel *QLabel;
	TLabel *VLabel;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ShowButClick(TObject *Sender);
	void __fastcall GraphPaintBoxPaint(TObject *Sender);
	void __fastcall A25SpinChange(TObject *Sender);
	void __fastcall A50SpinChange(TObject *Sender);
	void __fastcall A75SpinChange(TObject *Sender);
	void __fastcall SubButClick(TObject *Sender);
	void __fastcall MIndexSpinChange(TObject *Sender);
	void __fastcall GraphPaintBoxClick(TObject *Sender);
	void __fastcall MValueSpinChange(TObject *Sender);




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
