   M S B A M L   `   `   `  ���� G  CPlagiarismUI, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null7 clr-namespace:PlagiarismUI.ViewsPlagiarismUI.Views  &     PlagiarismUI.Views.LoadingWindow   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     @d2http://schemas.microsoft.com/expression/blend/2008     Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     2local clr-namespace:PlagiarismUI.Views       � Title$  LoadingWindow��$	��400��$	��600��.��� 
�������.+�A� $
��Left=�$��65��$��
410,30,0,0q�
���   �$��4��$	��Top=�$��75������ *BuldCFMsStepFinished+A� $
��Left=�$��65��$��
310,30,0,0q�
���   �$��4��$	��Top=�$��75�� J� RenderTransformOrigin$ -0.533,0.462&����� *BuildVocStepFinished+A� $
��Left=�$��65��$��
210,30,0,0q�
���   �$��4��$	��Top=�$��75������ *ExtractNgramsStepFinished+A� $
��Left=�$��65��$��410,110,0,0q�
���   �$��4��$	��Top=�$��75������ *ExamineResult+A� $
��Left=�$��65��$��
110,30,0,0q�
���   �$��4��$	��Top=�$��75������ *DevideTextToSegStepFinished+A� $
��Left=�$��65��$��	10,30,0,0q�
���   �$��4��$	��Top=�$��75������ *OmitStopWordsStepFinished+A� $
��Left=�$��65��$��310,110,0,0q�
���   �$��4��$	��Top=�$��75������ *CalcApproxMeasStepFinished+A� $
��Left=�$��65��$��210,110,0,0q�
���   �$��4��$	��Top=�$��75������ *CalcAQMeasureStepFinished+A� $
��Left=�$��65��$��110,110,0,0q�
���   �$��4��$	��Top=�$��75������ *BuildQsStepFinished+A� $
��Left=�$��65��$��
10,110,0,0q�
���   �$��4��$	��Top=�$��75������ *BuildSPsStepFinished+�� -    ��Name$ 
textBlock1��$
��Bold"�$��10(�$
��Left=�$��41��$��
120,45,0,0q�$
��Wrap=�$��divide Text into Chunks��$	��Top=�$��60���� -   $ textBlock1_Copy��$
��Bold"�$��10(�$
��Left=�$��31��$��
220,49,0,0q�$
��Wrap=�$��Extract NGrams��$	��Top=�$��55���� -   $ 	textBlock��$��10(�$
��Bold"�$
��Left=�$��31��$��	20,49,0,0q�$
��Wrap=�$��Omit StopWords��$	��Top=�$��55���� -   $ textBlock1_Copy1��$
��Bold"�$��10(�$
��Left=�$��20��$��
320,49,0,0q�$
��Wrap=�$	��Top=�$��55��$��	Build Voc���� -   $ textBlock1_Copy2��$
��Bold"�$��10(�$
��Left=�$��20��$��
420,49,0,0q�$
��Wrap=�$��Build CFM's��$	��Top=�$��55���� -   $ textBlock1_Copy3��$
��Bold"�$��10(�$
��Left=�$��30��$��423,130,0,0q�$
��Wrap=�$��Examine Results��$	��Top=�$��55���� -   $ textBlock1_Copy4��$
��Bold"�$��10(�$
��Left=�$��30��$��325,125,0,0q�$
��Wrap=�$��Calc Approx Error��$	��Top=�$��55���� -   $ textBlock1_Copy5��$
��Bold"�$��10(�$
��Left=�$��30��$��224,130,0,0q�$
��Wrap=�$��Calc Q measure��$	��Top=�$��55���� -	   $ textBlock1_Copy6��$
��Bold"�$��10(�$
��Left=�$��20��$��122,130,0,0q�$
��Wrap=�$��	Build Q's��$	��Top=�$��55���� -
   $ textBlock1_Copy7��$
��Bold"�$��10(�$
��Left=�$��20��$��
20,130,0,0q�$
��Wrap=�$��
Build SP's��$	��Top=�$��55��$ -1.545,0.25&��� -    ��Name$ backFromLoading��$��Back To Main Page��$
��Left=�$��30��$��
20,315,0,0q�$	��Top=�$	��105���� -   $ 
textBlock2��$
��Left=�$��18(�
���  ��$��	UltraBold"�$��30��$��	185,0,0,0q�$
��Wrap=�$��Algorithm Stages��$	��Top=�$	��170���� 