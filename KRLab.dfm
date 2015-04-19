object MainForm: TMainForm
  Left = 420
  Top = 270
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'MainForm'
  ClientHeight = 340
  ClientWidth = 1000
  Color = clBtnFace
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'Segoe UI'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  ScreenSnap = True
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 21
  object GraphPaintBox: TPaintBox
    Left = 328
    Top = 8
    Width = 313
    Height = 241
    OnClick = GraphPaintBoxClick
    OnPaint = GraphPaintBoxPaint
  end
  object MLabel1: TLabel
    Left = 824
    Top = 64
    Width = 64
    Height = 23
    Caption = 'MLabel1'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object MLabel2: TLabel
    Left = 824
    Top = 85
    Width = 64
    Height = 23
    Caption = 'MLabel2'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object QLabel: TLabel
    Left = 824
    Top = 24
    Width = 64
    Height = 23
    Caption = 'MLabel2'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object VLabel: TLabel
    Left = 824
    Top = 176
    Width = 47
    Height = 21
    Caption = 'VLabel'
  end
  object StringGrid: TStringGrid
    Left = 8
    Top = 8
    Width = 297
    Height = 241
    ColCount = 4
    RowCount = 6
    TabOrder = 0
  end
  object ShowBut: TButton
    Left = 8
    Top = 255
    Width = 297
    Height = 66
    Caption = 'ShowBut'
    TabOrder = 1
    OnClick = ShowButClick
  end
  object A25Spin: TSpinEdit
    Left = 424
    Top = 255
    Width = 70
    Height = 31
    MaxValue = 0
    MinValue = 0
    TabOrder = 2
    Value = 0
    OnChange = A25SpinChange
  end
  object A50Spin: TSpinEdit
    Left = 497
    Top = 255
    Width = 70
    Height = 31
    MaxValue = 0
    MinValue = 0
    TabOrder = 3
    Value = 0
    OnChange = A50SpinChange
  end
  object A75Spin: TSpinEdit
    Left = 571
    Top = 255
    Width = 70
    Height = 31
    MaxValue = 0
    MinValue = 0
    TabOrder = 4
    Value = 0
    OnChange = A75SpinChange
  end
  object IndexSpin: TSpinEdit
    Left = 328
    Top = 255
    Width = 70
    Height = 31
    MaxValue = 0
    MinValue = 0
    TabOrder = 5
    Value = 0
    OnChange = GraphPaintBoxClick
  end
  object AStringGrid: TStringGrid
    Left = 656
    Top = 8
    Width = 153
    Height = 241
    ColCount = 2
    RowCount = 6
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
    TabOrder = 6
  end
  object SubBut: TButton
    Left = 656
    Top = 255
    Width = 153
    Height = 66
    Caption = 'Submit'
    TabOrder = 7
    OnClick = SubButClick
  end
  object MIndexSpin: TSpinEdit
    Left = 824
    Top = 127
    Width = 70
    Height = 31
    MaxValue = 0
    MinValue = 0
    TabOrder = 8
    Value = 0
    OnChange = MIndexSpinChange
  end
  object MValueSpin: TSpinEdit
    Left = 900
    Top = 127
    Width = 70
    Height = 31
    MaxValue = 0
    MinValue = 0
    TabOrder = 9
    Value = 0
    OnChange = MValueSpinChange
  end
  object CalcBut: TButton
    Left = 824
    Top = 255
    Width = 158
    Height = 66
    Caption = 'Calculate'
    TabOrder = 10
    OnClick = CalcButClick
  end
end
