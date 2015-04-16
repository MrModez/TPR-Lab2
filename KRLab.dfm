object MainForm: TMainForm
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'MainForm'
  ClientHeight = 459
  ClientWidth = 875
  Color = clBtnFace
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'Segoe UI'
  Font.Style = []
  OldCreateOrder = False
  ScreenSnap = True
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 21
  object PaintBox1: TPaintBox
    Left = 328
    Top = 16
    Width = 313
    Height = 265
    OnPaint = PaintBox1Paint
  end
  object StringGrid: TStringGrid
    Left = 8
    Top = 24
    Width = 281
    Height = 217
    ColCount = 4
    RowCount = 6
    TabOrder = 0
  end
  object ShowBut: TButton
    Left = 8
    Top = 247
    Width = 281
    Height = 66
    Caption = 'ShowBut'
    TabOrder = 1
    OnClick = ShowButClick
  end
  object GraphBut: TButton
    Left = 328
    Top = 324
    Width = 217
    Height = 66
    Caption = 'Graph'
    TabOrder = 2
    OnClick = GraphButClick
  end
  object A25Spin: TSpinEdit
    Left = 328
    Top = 287
    Width = 70
    Height = 31
    MaxValue = 0
    MinValue = 0
    TabOrder = 3
    Value = 0
    OnChange = A25SpinChange
  end
  object A50Spin: TSpinEdit
    Left = 401
    Top = 287
    Width = 70
    Height = 31
    MaxValue = 0
    MinValue = 0
    TabOrder = 4
    Value = 0
    OnChange = A25SpinChange
  end
  object A75Spin: TSpinEdit
    Left = 475
    Top = 287
    Width = 70
    Height = 31
    MaxValue = 0
    MinValue = 0
    TabOrder = 5
    Value = 0
    OnChange = A25SpinChange
  end
  object IndexSpin: TSpinEdit
    Left = 571
    Top = 359
    Width = 70
    Height = 31
    MaxValue = 0
    MinValue = 0
    TabOrder = 6
    Value = 0
    OnChange = GraphButClick
  end
end
