object MainForm: TMainForm
  Left = 420
  Top = 270
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 
    #1052#1077#1090#1086#1076' '#1087#1088#1077#1076#1087#1086#1095#1090#1077#1085#1080#1081' '#1080' '#1079#1072#1084#1077#1097#1077#1085#1080#1081' '#1050#1080#1085#1080' '#1080' '#1056#1072#1081#1092#1072'. '#1060#1072#1073#1072#1088#1080#1089#1086#1074#1099' '#1047#1072#1075#1080#1088' '#1080' ' +
    #1058#1072#1075#1080#1088' '#1052#1054'-303'
  ClientHeight = 527
  ClientWidth = 716
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
    Left = 392
    Top = 32
    Width = 246
    Height = 241
    Visible = False
    OnClick = GraphPaintBoxClick
    OnPaint = GraphPaintBoxPaint
  end
  object MLabel1: TLabel
    Left = 222
    Top = 371
    Width = 35
    Height = 23
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object MLabel2: TLabel
    Left = 222
    Top = 400
    Width = 19
    Height = 23
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object QLabel: TLabel
    Left = 8
    Top = 502
    Width = 687
    Height = 23
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object VLabel: TLabel
    Left = 615
    Top = 305
    Width = 47
    Height = 21
    Caption = 'VLabel'
    Visible = False
  end
  object GLabel: TLabel
    Left = 694
    Top = 13
    Width = 4
    Height = 21
    Alignment = taRightJustify
  end
  object Label1: TLabel
    Left = 8
    Top = 279
    Width = 119
    Height = 23
    Caption = #1056#1072#1085#1078#1080#1088#1086#1074#1072#1085#1080#1077
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 415
    Top = 279
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
  object Label3: TLabel
    Left = 8
    Top = 8
    Width = 143
    Height = 23
    Caption = #1048#1089#1093#1086#1076#1085#1099#1077' '#1076#1072#1085#1085#1099#1077
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object MLabel: TLabel
    Left = 222
    Top = 311
    Width = 35
    Height = 23
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object Label4: TLabel
    Left = 392
    Top = 8
    Width = 135
    Height = 23
    Caption = #1043#1088#1072#1092#1080#1082' '#1082#1088#1080#1090#1077#1088#1080#1103
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object Label5: TLabel
    Left = 222
    Top = 279
    Width = 178
    Height = 23
    Caption = #1050#1086#1101#1092#1092'-'#1099' '#1073#1077#1079#1088#1072#1079#1083#1080#1095#1080#1103
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object StringGrid: TStringGrid
    Left = 8
    Top = 32
    Width = 378
    Height = 241
    ColCount = 4
    DefaultColWidth = 72
    RowCount = 6
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goEditing]
    TabOrder = 0
    OnKeyUp = StringGridKeyUp
  end
  object ShowBut: TButton
    Left = 312
    Top = 184
    Width = 65
    Height = 41
    Caption = 'ShowBut'
    TabOrder = 1
    Visible = False
    OnClick = ShowButClick
  end
  object A25Spin: TSpinEdit
    Left = 644
    Top = 189
    Width = 56
    Height = 31
    MaxValue = 0
    MinValue = 0
    TabOrder = 2
    Value = 0
    OnChange = A25SpinChange
  end
  object A50Spin: TSpinEdit
    Left = 644
    Top = 152
    Width = 56
    Height = 31
    MaxValue = 0
    MinValue = 0
    TabOrder = 3
    Value = 0
    OnChange = A50SpinChange
  end
  object A75Spin: TSpinEdit
    Left = 644
    Top = 112
    Width = 56
    Height = 31
    MaxValue = 0
    MinValue = 0
    TabOrder = 4
    Value = 0
    OnChange = A75SpinChange
  end
  object AStringGrid: TStringGrid
    Left = 8
    Top = 300
    Width = 208
    Height = 197
    ColCount = 2
    DefaultColWidth = 100
    RowCount = 6
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goEditing]
    TabOrder = 5
    OnKeyUp = AStringGridKeyUp
  end
  object SubBut: TButton
    Left = 312
    Top = 231
    Width = 65
    Height = 42
    Caption = 'Submit'
    TabOrder = 6
    Visible = False
    OnClick = SubButClick
  end
  object MIndexSpin0: TSpinEdit
    Left = 358
    Top = 299
    Width = 17
    Height = 31
    MaxValue = 0
    MinValue = 0
    TabOrder = 7
    Value = 0
    Visible = False
    OnChange = MIndexSpin0Change
  end
  object MValueSpin: TSpinEdit
    Left = 305
    Top = 338
    Width = 70
    Height = 31
    MaxValue = 0
    MinValue = 0
    TabOrder = 8
    Value = 0
    OnChange = MValueSpinChange
  end
  object CalcBut: TButton
    Left = 615
    Top = 332
    Width = 80
    Height = 86
    Caption = #1042#1099#1095#1080#1089#1083#1080#1090#1100
    TabOrder = 9
    Visible = False
    OnClick = CalcButClick
  end
  object RStringGrid: TStringGrid
    Left = 415
    Top = 299
    Width = 194
    Height = 197
    ColCount = 2
    DefaultColWidth = 92
    RowCount = 6
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing]
    TabOrder = 10
    OnClick = RStringGridClick
    RowHeights = (
      24
      24
      24
      24
      24
      24)
  end
  object StartBut: TButton
    Left = 312
    Top = 131
    Width = 65
    Height = 47
    Caption = 'StartBut'
    TabOrder = 11
    Visible = False
    OnClick = StartButClick
  end
  object LoadBut: TButton
    Left = 615
    Top = 424
    Width = 80
    Height = 73
    Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100
    TabOrder = 12
    OnClick = LoadButClick
  end
  object IndexSpin: TUpDown
    Left = 644
    Top = 40
    Width = 57
    Height = 25
    Max = 0
    Orientation = udHorizontal
    TabOrder = 13
    OnMouseUp = IndexSpinMouseUp
  end
  object MIndexSpin: TUpDown
    Left = 222
    Top = 340
    Width = 64
    Height = 25
    Max = 0
    Orientation = udHorizontal
    TabOrder = 14
    OnMouseUp = MIndexSpinMouseUp
  end
  object CoverPanel: TPanel
    Left = 6
    Top = 8
    Width = 3
    Height = 505
    BevelOuter = bvNone
    Caption = #1053#1072#1078#1084#1080#1090#1077', '#1095#1090#1086#1073#1099' '#1079#1072#1075#1088#1091#1079#1080#1090#1100' '#1092#1072#1081#1083
    TabOrder = 15
    OnClick = CoverPanelClick
  end
  object DatOpenDialog: TOpenDialog
    Filter = 'Data|*.dat'
    Left = 328
    Top = 272
  end
end
