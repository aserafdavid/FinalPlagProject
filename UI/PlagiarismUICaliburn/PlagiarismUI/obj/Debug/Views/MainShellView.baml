   M S B A M L   `   `   `  ����G  CPlagiarismUI, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null+clr-namespace:PlagiarismUIPlagiarismUI  5   	        PlagiarismUI.MainShellView   5   	   U QWPFToolkit, Version=3.5.40128.1, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35F 9http://schemas.microsoft.com/winfx/2006/xaml/presentation     5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   ,localclr-namespace:PlagiarismUI     5   	   -   5          � Title$  MainShellView��5	   	   $	��400��6   $	��600��6,    � DataContext 5      %   PlagiarismUI.MainShellViewModel  5   
   6%    � 	Resources 5      *   $PlagiarismUI.RadioBoolToIntConverter   radioBoolToIntConverter��%   &	          5   
   6(   5      .��5      � 
�������.+�5   
   �� -   5         ��Name$ 	infoImage��5      $��/Images/infoIcon.png��6#   $
��Left=�6B   $��62��6]   $��483,34,-7,0q�6i   $	��Top=�6~   $��77��6�    J� RenderTransformOrigin$ 0.519,0.919&�6�    � ToolTip 5      _� 5       �� ContentStringFormat$] WThis Application using math for analyze your text/article and trying to find Plagiarism��6   6�   5      �� 5   
   
���   �$��1q�6%   $
��Left=�69   $	��120��6T   $��	5,175,0,0q�6a   $	��Top=�6t   $	��465��6�   ._�5      �� -   5         ��Name$ comboBox��5      $
��Left=�6~   $��25��6�   $��	164,4,0,0q�6�   $	��Top=�6�   $	��120��6�   ��6*   �� *LanguageSelection+ �� SelectedItem 6T   �� *ChoosenLanguage+6�   5      �� 5"   
   -   5        	 ��Name$	 LoadTextLabl��5"      $
��Bold"�6&   $��Examination Text File:��68   $
��Left=�6Z   $��35��6u   $��	15,20,0,0q�6�   $	��Top=�6�   $	��145��6�   �� 5#   
   -   5        
 ��Name$
 
FileBrowse��5#      $��Browse ��6%   $
��Left=�67   $��25��6R   $��
165,20,0,0q�6^   $	��Top=�6r   $��95��6�    5$      _� 5%      .��5&      �� *(You must upload a file in a .txt format.6J   5'      5)      �� 5*   
   -   5        $	 PathToMainFile��5*      
���  ��$
��Left=�6c   $��25��6~   $��
260,20,0,0q�6�   $	��Top=�6�   $	��300��6�   $ 	0.476,0.2&�6�   ��6(   �� *PathToMainInputFile+6�   �� 5+   
   -   5        $	 SegSizeLabel��5+      $��Segment Size��6&   $
��Bold"�6>   $
��Left=�6P   $��30��6k   $��	20,50,0,0q�6w   $	��Top=�6�   $	��115��6�   �� 5-   
   -   5        $	 NgramSizeLabel��5-      $��
Ngram Size��6(   $
��Bold"�6=   $
��Left=�6O   $��30��6j   $��	15,85,0,0q�6v   $	��Top=�6�   $	��120��6�   �� 5/   
   -	   5         ��Name$ SegSizeInput��5/      $
��Left=�6p   $��30��6�   $��
165,55,0,0q�6�    �� TextWrapping$
 Wrap=�6�   $	��Top=�6�   $��80��6�   ��6S   �� *SegmentSize+6�   �� 53   
   -
   5        $ NgramSizeInput��53      $
��Left=�6p   $��29��6�   $��
165,91,0,0q�6�   $
 Wrap=�6�   $	��Top=�6�   $��80��6�   ��6U   �� *	NgramSize+6�   �� 57   
   -   5        $	 LoadTextLabl_Copy��57      $
��Bold"�6+   $��Stop Words TextFile:��6=   $
��Left=�6]   $��35��6x   $��
15,250,0,0q�6�   $	��Top=�6�   $	��140��6�   �� 58   
   -   5        $
 FileBrowseStopWordsButton��58      $��Browse ��64   $
��Left=�6F   $��25��6a   $��165,250,0,0q�6m   $	��Top=�6�   $��95��6�   $ 0.474,2&�6�   �� 59   
   -   5        $	 PathToStopWordsFile��59      
���  ��$
��Left=�6h   $��25��6�   $��260,250,0,0q�6�   $	��Top=�6�   $	��210��6�   $ 	0.476,0.2&�6�   ��6-   �� *PathToStopWordsFile+6�   	� 5:   
   -   5         	�Name$ radioButton��5:      $��Defult��6+   $
��Left=�6<   $��334,155,0,0q�6W   $	��Top=�6l   �� 5<   
   -   5        $ expander��5<      $
��Left=�6p   $��25��6�   $��345,325,0,0q�6�   $	��Top=�6�   $	��105��6�   $ 
0.81,0.143&�6�   ��6%   �� *RunSelection+ 6J   �� *
ChoosenRun+6�   �� 5>   
   -   5        $	
 Run��5>      $��Analyze Text��6C   $
��Bold"�6Z   
���  ��$
��Left=�6~   $��40��6�   $��470,315,0,0q�6�   $	��Top=�6�   $��90��6�   {�6   �� *AnalyzeEnabled+6�   �� 5A   
   -   5         ��Name$ InputSection��5A      
���  ��$
��Left=�6<   $
��Wrap=�6W   $��Algorithm input Section��6k   $	��Top=�6�   $��20,0,0,0q�6�   �� 5B   
   -   5        $ StopWordsSection��5B      
���  ��$
��Left=�6@   $��15��6[   $��
10,155,0,0q�6g   $
��Wrap=�6{   $��StopWords Input Section��6�   $	��Top=�6�   $	��150��6�   �� 5C   
   -   5        $ image��5C      $��/Images/MainPageImage.jpg��6   $
��Left=�6B   $	��120��6]   $��475,175,0,0q�6j   $	��Top=�6   $��98��6�   $ 0.607,0.783&�6�   	� 5E   
   -   5        $ Academic��5E      $��Academic Stopword List��6�   $
��Left=�6�   $��20��6�   $��5,220,0,132.5q�6�   $	��155��6�    d� 	IsChecked 6(   �� *StopWordsListChecked+ �� 	Converter# [   �� ConverterParameter$ 1��6�   	� 5F   
   -   5        $ 
Literature��5F      $��Literature Stopwords List��6�   $
��Left=�6�   $��20��6�   $��160,220,0,132.5q�6�   $	��160��6  $ 
2.158,-0.5&�6   6+   �� *StopWordsListChecked+# [  $ 2��6  	� 5G   
   -   5        $ Custom��5G      $��Custom StopWords List��6�   $
��Left=�6�   $��20��6�   $��315,220,0,132.5q�6�   $	��155��6�   $ 
2.158,-0.5&�6	   6'   �� *StopWordsListChecked+# [  $ 3��6	  �� 5H   
   -   5        $	 LanguageLabel��5H      $
��Bold"�6'   $��Stop Words Language:��6;   $
��Left=�6[   $��35��6v   $��
20,180,0,0q�6�   $	��Top=�6�   $	��210��6�   $ 0.429,-1.143&�6�   5I      5J      