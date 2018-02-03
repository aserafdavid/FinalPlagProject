using PlagiarismUI.InfraS;
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
            //ResultPATH = "D:\\RunPlag\\Engine\\\\tempFiles\\2018_02_03-19_29_05";
            //string FixedPath = Directory.GetCurrentDirectory()+"\\"+ ResultPATH;        
            //int i = FixedPath.IndexOf("\\\\");
            //string last = FixedPath.Substring(i+1);
            //string first = FixedPath.Substring(0, i );
            //string PATH = first + last;
            //System.Windows.MessageBox.Show(PATH + "David After", "Invalid input", MessageBoxButton.OK);
            //char[] str = new char[FixedPath.Length];
            //char[] str2 = new char[FixedPath.Length];
            //str = FixedPath.ToCharArray();
            //for (int i =0;i< FixedPath.Length-1;i++)
            //{
            //    if(str[i] == '\\' && str[i+1] == '\\')
            //    {
            //        continue;
            //    }
            //    str2[i] = str[i];
            //}
            //FixedPath = new string(str2);
            //ResultPATH = PATH;

            System.Windows.MessageBox.Show(ResultPATH + "-AdirBeforeResults", "Invalid input", MessageBoxButton.OK);

            string FilePath = ResultPATH;
            int clusterdCounter = 0;
            if (ConnectionManager.AlgToRun == "Clustered" || ConnectionManager.AlgToRun == "BOTH")
            {
                
                List <int> ClusteredNums = new List<int>();


                FilePath += "\\Results\\CL_Results.txt";
                //System.Windows.MessageBox.Show(FilePath, "Invalid input", 
                //Button.OK);
                if (!File.Exists(FilePath))
                {
                    //System.Windows.MessageBox.Show("Can't load CL_Results.txt", "Invalid input", MessageBoxButton.OK);                  
                    this.BackToMain();

                }

                StreamReader sr = new StreamReader(FilePath);
                //System.Windows.MessageBox.Show("after Streamreader Creation", "Invalid input", MessageBoxButton.OK);
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
                //System.Windows.MessageBox.Show(PATH + "LoadDSChart", "Invalid input", MessageBoxButton.OK);

                LoadDSChart();
            }
            if (ConnectionManager.AlgToRun == "Dynamical" || ConnectionManager.AlgToRun == "BOTH")
            {
                //System.Windows.MessageBox.Show(PATH + "LoadLineChartData", "Invalid input", MessageBoxButton.OK);
      
                LoadLineChartData(ResultPATH);
            }
        }


        private void LoadLineChartData(string ResultPATH)
        {
            string FilePath = ResultPATH;
            //System.Windows.MessageBox.Show(FilePath, "Invalid input", MessageBoxButton.OK);
            //  string  FilePath = "D:\\finalProjectPlagiarism\\tempFiles\\2018_01_28-22_08_34\\Results";
            FilePath += "\\Results\\DS_Results.txt";
            //System.Windows.MessageBox.Show(FilePath, "Invalid input", MessageBoxButton.OK);
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

