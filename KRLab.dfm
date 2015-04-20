object MainForm: TMainForm
  Left = 420
  Top = 270
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 
    #1052#1077#1090#1086#1076' '#1087#1088#1077#1076#1087#1086#1095#1090#1077#1085#1080#1081' '#1080' '#1079#1072#1084#1077#1097#1077#1085#1080#1081' '#1050#1080#1085#1080' '#1080' '#1056#1072#1081#1092#1072'. '#1060#1072#1073#1072#1088#1080#1089#1086#1074' '#1047#1072#1075#1080#1088' '#1052#1054'-' +
    '303'
  ClientHeight = 471
  ClientWidth = 712
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
    Left = 383
    Top = -7
    Width = 258
    Height = 241
    Visible = False
    OnClick = GraphPaintBoxClick
    OnPaint = GraphPaintBoxPaint
  end
  object MLabel1: TLabel
    Left = 224
    Top = 280
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
    Left = 224
    Top = 309
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
    Left = 8
    Top = 435
    Width = 554
    Height = 23
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object VLabel: TLabel
    Left = 568
    Top = 276
    Width = 47
    Height = 21
    Caption = 'VLabel'
  end
  object GLabel: TLabel
    Left = 691
    Top = 38
    Width = 4
    Height = 21
    Alignment = taRightJustify
  end
  object Label1: TLabel
    Left = 8
    Top = 247
    Width = 129
    Height = 23
    Caption = #1056#1072#1085#1078#1080#1088#1086#1074#1072#1085#1085#1080#1077
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 383
    Top = 247
    Width = 76
    Height = 23
    Caption = #1056#1077#1079#1091#1083#1100#1090#1072#1090
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object StringGrid: TStringGrid
    Left = 8
    Top = 8
    Width = 369
    Height = 226
    ColCount = 4
    DefaultColWidth = 70
    RowCount = 6
    TabOrder = 0
  end
  object ShowBut: TButton
    Left = 312
    Top = 145
    Width = 65
    Height = 41
    Caption = 'ShowBut'
    TabOrder = 1
    Visible = False
    OnClick = ShowButClick
  end
  object A25Spin: TSpinEdit
    Left = 647
    Top = 189
    Width = 53
    Height = 31
    MaxValue = 0
    MinValue = 0
    TabOrder = 2
    Value = 0
    OnChange = A25SpinChange
  end
  object A50Spin: TSpinEdit
    Left = 647
    Top = 152
    Width = 53
    Height = 31
    MaxValue = 0
    MinValue = 0
    TabOrder = 3
    Value = 0
    OnChange = A50SpinChange
  end
  object A75Spin: TSpinEdit
    Left = 647
    Top = 112
    Width = 53
    Height = 31
    MaxValue = 0
    MinValue = 0
    TabOrder = 4
    Value = 0
    OnChange = A75SpinChange
  end
  object AStringGrid: TStringGrid
    Left = 8
    Top = 276
    Width = 201
    Height = 153
    ColCount = 2
    DefaultColWidth = 128
    RowCount = 6
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
    TabOrder = 5
    ColWidths = (
      128
      56)
  end
  object SubBut: TButton
    Left = 312
    Top = 192
    Width = 65
    Height = 42
    Caption = 'Submit'
    TabOrder = 6
    Visible = False
    OnClick = SubButClick
  end
  object MIndexSpin: TSpinEdit
    Left = 224
    Top = 359
    Width = 47
    Height = 31
    MaxValue = 0
    MinValue = 0
    TabOrder = 7
    Value = 0
    OnChange = MIndexSpinChange
  end
  object MValueSpin: TSpinEdit
    Left = 284
    Top = 359
    Width = 70
    Height = 31
    MaxValue = 0
    MinValue = 0
    TabOrder = 8
    Value = 0
    OnChange = MValueSpinChange
  end
  object CalcBut: TButton
    Left = 568
    Top = 363
    Width = 127
    Height = 66
    Caption = #1042#1099#1095#1080#1089#1083#1080#1090#1100
    TabOrder = 9
    OnClick = CalcButClick
  end
  object RStringGrid: TStringGrid
    Left = 383
    Top = 276
    Width = 179
    Height = 153
    ColCount = 2
    DefaultColWidth = 70
    RowCount = 6
    TabOrder = 10
  end
  object StartBut: TButton
    Left = 312
    Top = 92
    Width = 65
    Height = 47
    Caption = 'StartBut'
    TabOrder = 11
    Visible = False
    OnClick = StartButClick
  end
  object LoadBut: TButton
    Left = 8
    Top = 8
    Width = 89
    Height = 65
    Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100
    TabOrder = 12
    OnClick = LoadButClick
  end
  object IndexSpin: TUpDown
    Left = 647
    Top = 65
    Width = 49
    Height = 25
    Orientation = udHorizontal
    TabOrder = 13
    OnMouseUp = IndexSpinMouseUp
  end
  object DatOpenDialog: TOpenDialog
    Left = 328
    Top = 248
  end
end
