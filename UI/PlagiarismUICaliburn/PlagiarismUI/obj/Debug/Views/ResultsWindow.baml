   M S B A M L   `   `   `  ����G  CPlagiarismUI, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null7 clr-namespace:PlagiarismUI.ViewsPlagiarismUI.Views  5   	   | xSystem.Windows.Controls.DataVisualization.Toolkit, Version=3.5.40128.1, Culture=neutral, PublicKeyToken=31bf3856ad364e35�{clr-namespace:System.Windows.Controls.DataVisualization.Charting;assembly=System.Windows.Controls.DataVisualization.Toolkit2System.Windows.Controls.DataVisualization.Charting 5   	   [ WSystem.Windows.Forms, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089Y@clr-namespace:System.Windows.Forms;assembly=System.Windows.FormsSystem.Windows.Forms 5   	   L HDataGrid2DLibrary, Version=1.0.0.0, Culture=neutral, PublicKeyToken=nullP:clr-namespace:DataGrid2DLibrary;assembly=DataGrid2DLibraryDataGrid2DLibrary 5
      &     PlagiarismUI.Views.ResultsWindow   5   	   U QWPFToolkit, Version=3.5.40128.1, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35F 9http://schemas.microsoft.com/winfx/2006/xaml/presentation     5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   2local clr-namespace:PlagiarismUI.Views     5   	   �DVC{clr-namespace:System.Windows.Controls.DataVisualization.Charting;assembly=System.Windows.Controls.DataVisualization.Toolkit     5   	   Owf@clr-namespace:System.Windows.Forms;assembly=System.Windows.Forms     5   	   Kdg2d:clr-namespace:DataGrid2DLibrary;assembly=DataGrid2DLibrary     5
        � Title$  ResultsWindow��5   	   $	��450��6    $	��600��6-   .��5      � ��6   �� *GridBackGround+.+�5   
   �� 
�������$��
0,0,0,-2.5q�6+   $	��425��6?   $	��Top=�6M   .@�5      �� $��DS��6   .��5      � .+�5      >  8System.Windows.Controls.DataVisualization.Charting.Chart  -   5        $��MyChart��5   !   $��197,0,-3,92q�60   
�������$	��305��6\   $��Bottom=�6i   $
��Left=�6�   $	��395��6�      Series 5      C  =System.Windows.Controls.DataVisualization.Charting.LineSeries  H  BSystem.Windows.Controls.DataVisualization.Charting.DataPointSeries   IndependentValueBinding 6-   ��  �� Path$	 Key�   DependentValueBinding 6Z   �� $ Value�5      F  @System.Windows.Controls.DataVisualization.Charting.ScatterSeries  5      $��-10,-105,-115,28q�61   $��Right=�6K   $	��390��6g    J� RenderTransformOrigin$ 0.344,0.505&�6s   $	��300��6�   $��Bottom=�6�   5      �� 5      -   5         ��Name$ button��5      $��Button��6-   $
��Left=�6>   $��45��6Y   $��
12,330,0,0q�6e   $	��Top=�6y   $	��140��6�   5      5      �� 5      $��	Clustered��6   .��5      � .+�5*      �� -   5        $ button3��5*      $��Button��6.   $
��Left=�6?   $��45��6Z   $��
12,330,0,0q�6f   $	��Top=�6z   $	��140��6�   $��3��6�   &   System.Windows.Controls.DataGrid  5,      -   5          Name$ 	GraphGrid��5,       $
��Left=�64   $	��230��6O   $��
217,40,0,0q�6\   $	��Top=�6p   $	��360��6�   5-      5/      50      51       � 52   
   -   5          �Name$ frame2��52      $��10q�6    
���   �$
��Bold"�6J   $��Algorithm Details:��6]   $��-5,25,394,0q�6|   $	��280��6�   $	��Top=�6�   �� 53   
   -   5        	 ��Name$	 label5��53      $
��Left=�6=   $��30��6X   $��
112,35,0,0q�6d   $	��Top=�6x   $��70��6�   ��6    �� *
TextName+6�   �� 54   
   -   5        $	 label6��54      $
��Left=�6<   $��30��6W   $��
112,75,0,0q�6c   $	��Top=�6w   $��70��6�   ��6    �� *	SegSize+6�   �� 55   
   -   5        $	 label7��55      $
��Left=�6?   $��30��6Z   $��112,120,0,0q�6f   $	��Top=�6{   $��70��6�   ��6    �� *	NGramSize+6�   �� 56   
   -	   5        $	 label7_Copy��56      $
��Left=�6C   $��30��6^   $��112,155,0,0q�6j   $	��Top=�6   $��70��6�   ��6%   �� *
Clusters+6�   �� 57   
   -
   5        $	 label7_Copy1��57      $
��Left=�6?   $��30��6Z   $��112,200,0,0q�6f   $	��Top=�6{   $��70��6�   ��6&   �� *Lang+6�   �� 58   
   -   5        $	 label��58      $��
Text Name:��6   $
��Bold"�64   $
��Left=�6F   $��30��6a   $��	10,60,0,0q�6m   $	��Top=�6�   $��85��6�   �� 59   
   -   5        $	 label1��59      $��Segment Size:��6    $
��Bold"�68   $
��Left=�6J   $��30��6e   $��
10,100,0,0q�6q   $	��Top=�6�   $��90��6�   �� 5:   
   -   5        $	 label2��5:      $��Ngram Size:��6    $
��Left=�66   $
��Bold"�6Q   $��30��6c   $��
10,140,0,0q�6o   $	��Top=�6�   $��90��6�   �� 5;   
   -   5        $	 label3��5;      $��
#Clusters:��6    $
��Left=�65   $��30��6P   $
��Bold"�6\   $��
10,185,0,0q�6n   $	��Top=�6�   $��95��6�   �� 5<   
   -   5        $	 label4��5<      $��	Language:��6    $
��Left=�64   $
��Bold"�6O   $��30��6a   $��
10,230,0,0q�6m   $	��Top=�6�   $��90��6�   5>      5?      