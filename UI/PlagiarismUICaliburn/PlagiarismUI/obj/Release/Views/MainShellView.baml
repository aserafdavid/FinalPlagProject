   M S B A M L   `   `   `  ���� G  CPlagiarismUI, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null+clr-namespace:PlagiarismUIPlagiarismUI       PlagiarismUI.MainShellView   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     @d2http://schemas.microsoft.com/expression/blend/2008     Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     ,localclr-namespace:PlagiarismUI     -     � Title$  MainShellView��$	��400��$	��600�� � DataContext %   PlagiarismUI.MainShellViewModel   � 	Resources *   $PlagiarismUI.RadioBoolToIntConverter   radioBoolToIntConverter��%   &	          .��� 
�������.+��� -    ��Name$ 	infoImage��$��/Images/infoIcon.png��$
��Left=�$��62��$��483,34,-7,0q�$	��Top=�$��77�� J� RenderTransformOrigin$ 0.519,0.919&� � ToolTip _�  �� ContentStringFormat$] WThis Application using math for analyze your text/article and trying to find Plagiarism���� 
���   �$��1q�$
��Left=�$	��120��$��	5,175,0,0q�$	��Top=�$	��465��._��� -    ��Name$ comboBox��$
��Left=�$��25��$��	164,4,0,0q�$	��Top=�$	��120������ *LanguageSelection+ �� SelectedItem �� *ChoosenLanguage+�� -   	 ��Name$	 LoadTextLabl��$
��Bold"�$��Examination Text File:��$
��Left=�$��35��$��	15,20,0,0q�$	��Top=�$	��145���� -   
 ��Name$
 
FileBrowse��$��Browse ��$
��Left=�$��25��$��
165,20,0,0q�$	��Top=�$��95�� _� .���� *(You must upload a file in a .txt format.�� -   $	 PathToMainFile��
���  ��$
��Left=�$��25��$��
260,20,0,0q�$	��Top=�$	��300��$ 	0.476,0.2&����� *PathToMainInputFile+�� -   $	 SegSizeLabel��$��Segment Size��$
��Bold"�$
��Left=�$��30��$��	20,50,0,0q�$	��Top=�$	��115���� -   $	 NgramSizeLabel��$��
Ngram Size��$
��Bold"�$
��Left=�$��30��$��	15,85,0,0q�$	��Top=�$	��120���� -	    ��Name$ SegSizeInput��$
��Left=�$��30��$��
165,55,0,0q� �� TextWrapping$
 Wrap=�$	��Top=�$��80������ *SegmentSize+�� -
   $ NgramSizeInput��$
��Left=�$��29��$��
165,91,0,0q�$
 Wrap=�$	��Top=�$��80������ *	NgramSize+�� -   $	 LoadTextLabl_Copy��$
��Bold"�$��Stop Words TextFile:��$
��Left=�$��35��$��
15,250,0,0q�$	��Top=�$	��140���� -   $
 FileBrowseStopWordsButton��$��Browse ��$
��Left=�$��25��$��165,250,0,0q�$	��Top=�$��95��$ 0.474,2&��� -   $	 PathToStopWordsFile��
���  ��$
��Left=�$��25��$��260,250,0,0q�$	��Top=�$	��210��$ 	0.476,0.2&����� *PathToStopWordsFile+	� -    	�Name$ radioButton��$��Defult��$
��Left=�$��334,155,0,0q�$	��Top=��� -   $ expander��$
��Left=�$��25��$��345,325,0,0q�$	��Top=�$	��105��$ 
0.81,0.143&����� *RunSelection+ �� *
ChoosenRun+�� -   $	
 Run��$��Analyze Text��$
��Bold"�
���  ��$
��Left=�$��40��$��470,315,0,0q�$	��Top=�$��90��{��� *AnalyzeEnabled+�� -    ��Name$ InputSection��
���  ��$
��Left=�$
��Wrap=�$��Algorithm input Section��$	��Top=�$��20,0,0,0q��� -   $ StopWordsSection��
���  ��$
��Left=�$��15��$��
10,155,0,0q�$
��Wrap=�$��StopWords Input Section��$	��Top=�$	��150���� -   $ image��$��/Images/MainPageImage.jpg��$
��Left=�$	��120��$��475,175,0,0q�$	��Top=�$��98��$ 0.607,0.783&�	� -   $ Academic��$��Academic Stopword List��$
��Left=�$��20��$��5,220,0,132.5q�$	��155�� d� 	IsChecked �� *StopWordsListChecked+ �� 	Converter# [   �� ConverterParameter$ 1��	� -   $ 
Literature��$��Literature Stopwords List��$
��Left=�$��20��$��160,220,0,132.5q�$	��160��$ 
2.158,-0.5&� �� *StopWordsListChecked+# [  $ 2��	� -   $ Custom��$��Custom StopWords List��$
��Left=�$��20��$��315,220,0,132.5q�$	��155��$ 
2.158,-0.5&� �� *StopWordsListChecked+# [  $ 3���� -   $	 LanguageLabel��$
��Bold"�$��Stop Words Language:��$
��Left=�$��35��$��
20,180,0,0q�$	��Top=�$	��210��$ 0.429,-1.143&�