using PlagiarismUI.ViewModels;
using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.DataVisualization.Charting;
using System.Windows.Media;

namespace PlagiarismUI.Views
{
    /// <summary>
    /// Interaction logic for ResultsWindow.xaml
    /// </summary>
    public partial class ResultsWindow : Window
    {
        private Window _MainWindow;
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

        }

        public ResultsWindow(Window mainWindow)
        {
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

