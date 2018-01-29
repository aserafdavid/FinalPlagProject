using PlagiarismUI.ViewModels;
using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.DataVisualization.Charting;
using System.Windows.Documents;
using System.Windows.Media;

namespace PlagiarismUI.Views
{

    public class ClusterString
    {
        public int ClusterId { get; set; }
        public string Data { get; set; }
    }

    /// <summary>
    /// Interaction logic for ResultsWindow.xaml
    /// </summary>
    public partial class ResultsWindow : Window
    {
        private Window _MainWindow;

        public List<ClusterString> ClusteredStrings { get; set; } = new List<ClusterString>();

        private void LoadDSChart()
        {
            //TODO Adir need to load graph here->
            //I think the graph should be build as a grid ask idan just for case


            // DataGrid myGraphDataGrid = (DataGrid)this.FindName("GraphGrid");
            //for (int i = 0; i < 10; i++)
            // {
            //     DataGridRow row = new DataGridRow();
            //     myGraphDataGrid.Items.Add(row);
            //     for (int j = 0; j < 10; j++)
            //     {
            //         //DataGridCell cell = new DataGridCell();
            //         //cell.Background = Brushes.Blue;
            //         //myGraphDataGrid.Items.Add(cell);
            //     }


            //}

            var flowDocument = (FlowDocument)FindName("FlowDocument");
            var paragraph = new Paragraph();
            foreach(var clusterString in ClusteredStrings)
            {
                var run = new Run($"{clusterString.Data} ");
                run.Background = clusterString.ClusterId % 3 == 0 ? Brushes.Red :
                                       clusterString.ClusterId % 3 == 1 ? Brushes.Green :
                                       Brushes.Blue;
                paragraph.Inlines.Add(run);
            }
            flowDocument.Blocks.Add(paragraph);
        }

        public ResultsWindow(Window mainWindow)
        {
            for(int i = 0; i < 900; i++)
                ClusteredStrings.Add( new ClusterString { ClusterId = i % 3, Data = $"cluster {i} string" } );

            _MainWindow = mainWindow;
            InitializeComponent();
            DataContext = new ResultwindowViewModel();
            
            LoadLineChartData();
            LoadDSChart();
        }
        private void LoadLineChartData()
        {
            ((LineSeries)MyChart.Series[0]).ItemsSource =
        new KeyValuePair<DateTime, int>[]{
        new KeyValuePair<DateTime,int>(DateTime.Now, 100),
        new KeyValuePair<DateTime,int>(DateTime.Now.AddMonths(1), 130),
        new KeyValuePair<DateTime,int>(DateTime.Now.AddMonths(2), 150),
        new KeyValuePair<DateTime,int>(DateTime.Now.AddMonths(3), 125),
        new KeyValuePair<DateTime,int>(DateTime.Now.AddMonths(4),155) };

        }


        //////////////
       



    }


}

