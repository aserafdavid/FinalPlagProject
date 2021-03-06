﻿using PlagiarismUI.InfraS;
using PlagiarismUI.ViewModels;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Threading;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.DataVisualization.Charting;
using System.Windows.Documents;
using System.Windows.Forms;
using System.Windows.Media;

namespace PlagiarismUI.Views
{

    public class ClusterString
    {
        public int ClusterId { get; set; }
        public string Data { get; set; }
    }

    public class DSstring
    {
        public int Id { get; set; }
        public double Data { get; set; }
    }
    public partial class ResultsWindow : Window
    {
        static bool XClicked = true;
        private Window _MainWindow;

        public List<ClusterString> ClusteredStrings { get; set; } = new List<ClusterString>();
        public List<DSstring> DSstrings { get; set; } = new List<DSstring>();


        private void LoadDSChart()
        {

            var flowDocument = (FlowDocument)FindName("FlowDocument");
            var paragraph = new Paragraph();
            foreach (var clusterString in ClusteredStrings)
            {
                var run = new Run($"{clusterString.Data} ");
                run.Background = clusterString.ClusterId % 3 == 0 ? Brushes.Red :
                                       clusterString.ClusterId % 3 == 1 ? Brushes.Green :
                                       Brushes.Blue;
                paragraph.Inlines.Add(run);
            }
            flowDocument.Blocks.Add(paragraph);
        }


        public ResultsWindow(Window mainWindow, string ResultPATH)
        {

            string FilePath = ResultPATH;
            int clusterdCounter = 0;
            if (ConnectionManager.AlgToRun == "Clustered" || ConnectionManager.AlgToRun == "BOTH")
            {
                
                List <int> ClusteredNums = new List<int>();


                FilePath += "\\Results\\CL_Results.txt";

                if (!File.Exists(FilePath))
                {
                                   
                    this.BackToMain();

                }

                StreamReader sr = new StreamReader(FilePath);
                string line = sr.ReadLine();
                while (line != null && line.Length > 2)
                {
                    string[] split = line.Split('\t');
                    if (split.Length == 2)
                    {
                        int Id = int.Parse(split[0]);
                        if(! ClusteredNums.Contains(Id))
                        {
                            clusterdCounter++;
                            ClusteredNums.Add(Id);
                        }
                        ClusteredStrings.Add(new ClusterString { ClusterId = Id, Data = split[1] });
                    }
                    else
                    {
                        int Id = int.Parse(split[0]);
                        ClusteredStrings.Add(new ClusterString { ClusterId = Id, Data = line.Substring(split[0].Length, line.Length - split[0].Length) });
                    }
                    line = sr.ReadLine();
                }
            }
            _MainWindow = mainWindow;
            
            InitializeComponent();
            if (ConnectionManager.AlgToRun == "Clustered")
                  ((TabItem)tabControl.Items[1]).IsSelected = true;
            string NgramSize = InfraS.ConnectionManager.NgramSize;
            string segSize = InfraS.ConnectionManager.segSize;
            string fileName = InfraS.ConnectionManager.fileName;
            DataContext = new ResultwindowViewModel(clusterdCounter.ToString(), NgramSize, fileName, segSize);
            
            if (ConnectionManager.AlgToRun == "Clustered" || ConnectionManager.AlgToRun == "BOTH")
            {

                LoadDSChart();
            }
            if (ConnectionManager.AlgToRun == "Dynamical" || ConnectionManager.AlgToRun == "BOTH")
            {
      
                LoadLineChartData(ResultPATH);
            }
        }


        private void LoadLineChartData(string ResultPATH)
        {
            string FilePath = ResultPATH;
            FilePath += "\\Results\\DS_Results.txt";
            if (!File.Exists(FilePath))
            {
                System.Windows.MessageBox.Show("Can't load DS_Results.txt", "Invalid input", MessageBoxButton.OK);
                this.BackToMain();

            }


            StreamReader sr = new StreamReader(FilePath);
            var cars = new ObservableCollection<DSstring>();




            string line = sr.ReadLine();
            int SegNum = 0;
            while (line != null && line.Length > 2)
            {
                string[] split = line.Split('\t');
                if (split.Length >= 2  && split[0]!="")
                {
                    DSstrings.Add(new DSstring { Id = SegNum, Data = Double.Parse(split[0]) });
                    SegNum++;
                }
                line = sr.ReadLine();
            }
            var GrpSource = ((LineSeries)MyChart.Series[0]).ItemsSource;
            KeyValuePair<int, double>[] Source = new KeyValuePair<int, double>[SegNum];

            for (int i = 0 ; i < SegNum; i++)
            {
                Source[i] = new KeyValuePair<int, double>(DSstrings[i].Id, DSstrings[i].Data);
            }
            ((LineSeries)MyChart.Series[0]).ItemsSource = Source;

        

        }

        private void BackToMain(object sender, RoutedEventArgs e)
        {
            ConnectionManager.GetEnginePipe().sendEngineMove("CANCELRUN");
              string ans = ConnectionManager.GetEnginePipe().getEngineMessage();
            if (ans == "ACCEPTED")
            {
                ConnectionManager.GetEnginePipe().close();
                ConnectionManager.GetUIenginePipe().close();
            }
            else
            {
                //Pop up message and exit
            }

            MainShellView MV = _MainWindow as MainShellView;
            MV.LoadAgain();
            this.Close();
            MV.Show();
           
        }





        private void BackToMain()
        {
            ConnectionManager.GetEnginePipe().sendEngineMove("CANCELRUN");
            string ans = ConnectionManager.GetEnginePipe().getEngineMessage();
            if (ans == "ACCEPTED")
            {
                ConnectionManager.GetEnginePipe().close();
                ConnectionManager.GetUIenginePipe().close();
            }
            else
            {
                //Pop up message and exit
            }

            MainShellView MV = _MainWindow as MainShellView;
            MV.LoadAgain();
            this.Close();
            MV.Show();

        }
        private void OnWindowClosing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            if (XClicked)
            {
                ConnectionManager.GetEnginePipe().sendEngineMove("QUIT");
                ConnectionManager.GetEnginePipe().getEngineMessage();
            }

            XClicked = true;
        }

    }


}

