object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 728
  ClientWidth = 1116
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  OnCreate = FormCreate
  TextHeight = 15
  object memoSalida: TMemo
    Left = 727
    Top = 360
    Width = 327
    Height = 177
    Lines.Strings = (
      'memoSalida')
    TabOrder = 0
  end
  object comboDestino: TComboBox
    Left = 264
    Top = 187
    Width = 145
    Height = 23
    TabOrder = 1
    Text = 'Destino'
  end
  object grupoRutas: TGroupBox
    Left = 727
    Top = 143
    Width = 201
    Height = 162
    Caption = 'Conexiones'
    TabOrder = 2
    object Edit6: TEdit
      Left = 40
      Top = 66
      Width = 121
      Height = 23
      TabOrder = 0
      Text = 'ID Ciudad 1'
    end
    object Edit7: TEdit
      Left = 40
      Top = 95
      Width = 121
      Height = 23
      TabOrder = 1
      Text = 'ID Ciudad 2'
    end
    object Edit8: TEdit
      Left = 40
      Top = 124
      Width = 121
      Height = 23
      TabOrder = 2
      Text = 'Distancia (km)'
    end
    object Button6: TButton
      Left = 40
      Top = 24
      Width = 121
      Height = 25
      Caption = 'Agregar conexi'#243'n'
      TabOrder = 3
      OnClick = Button6Click
    end
  end
  object comboOrigen: TComboBox
    Left = 264
    Top = 158
    Width = 145
    Height = 23
    TabOrder = 3
    Text = 'Origen'
  end
  object grupoCiudades: TGroupBox
    Left = 456
    Top = 143
    Width = 201
    Height = 162
    Caption = 'Ciudades'
    TabOrder = 4
    object Edit4: TEdit
      Left = 40
      Top = 95
      Width = 121
      Height = 23
      TabOrder = 0
      Text = 'Coordenada X'
    end
    object Edit5: TEdit
      Left = 40
      Top = 124
      Width = 121
      Height = 23
      TabOrder = 1
      Text = 'Coordenada Y'
    end
    object Edit3: TEdit
      Left = 40
      Top = 66
      Width = 121
      Height = 23
      TabOrder = 2
      Text = 'Nombre'
    end
    object Button5: TButton
      Left = 32
      Top = 27
      Width = 137
      Height = 25
      Caption = 'Agregar ciudad'
      TabOrder = 3
      OnClick = Button5Click
    end
  end
  object Button7: TButton
    Left = 727
    Top = 56
    Width = 98
    Height = 25
    Caption = 'Cargar Archivo'
    TabOrder = 5
    OnClick = Button7Click
  end
  object Button4: TButton
    Left = 520
    Top = 56
    Width = 113
    Height = 25
    Caption = 'Guardar en Archivo'
    TabOrder = 6
    OnClick = Button4Click
  end
  object Button3: TButton
    Left = 334
    Top = 112
    Width = 75
    Height = 25
    Caption = 'Cortar ruta'
    TabOrder = 7
    OnClick = Button3Click
  end
  object Button2: TButton
    Left = 248
    Top = 112
    Width = 80
    Height = 25
    Caption = 'Calcular ruta'
    TabOrder = 8
    OnClick = Button2Click
  end
  object Button1: TButton
    Left = 296
    Top = 56
    Width = 75
    Height = 25
    Caption = 'Ver ciudades'
    TabOrder = 9
    OnClick = Button1Click
  end
  object grillaMatriz: TStringGrid
    Left = 200
    Top = 360
    Width = 457
    Height = 265
    TabOrder = 10
  end
end
