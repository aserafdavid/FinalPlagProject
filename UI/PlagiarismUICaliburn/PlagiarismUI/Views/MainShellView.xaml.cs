using PlagiarismUI.InfraS;
using PlagiarismUI.Views;
using System;
using System.Threading;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Text.RegularExpressions;
using System.Windows.Media;
using System.IO;

namespace PlagiarismUI
{
    /// <summary>
    /// Interaction logic for MainShellView.xaml
    /// </summary>
    public partial class MainShellView : Window
    {
        public Pipe enginePipe;
        public volatile bool varsSended = false;


        
        public MainShellView()
        {
            ////for debug
            //ResultsWindow rw = new ResultsWindow(this);
            //this.Hide();
            //rw.ShowDialog();
            Thread newPipe = new Thread(connectNewPipe);
            newPipe.IsBackground = true;
            newPipe.Start();
            InitializeComponent();
            this.DataContext = new MainShellViewModel();
        }




        private bool StartBackgroundWork()
        {
            bool res = true;
            var DC = this.DataContext as MainShellViewModel;
            //int ngramSize = int.Parse(DC.NgramSize);
            //int segSize = int.Parse(DC.SegmentSize);
            if (DC.PathToMainInputFile == "No File Choosen")
            {
                MessageBox.Show("Please Insert Examination File input", "Invalid input", MessageBoxButton.OK);
                res = false;
            }
            if(DC.StopWordsListChecked == 3 && DC.PathToStopWordsFile == "No File Choosen")
            {
                MessageBox.Show("Please Insert StopWords List File input or Choose an existing one \n Note: you can run algorithm without omitting stop words by unchecking the StopWords CheckBox", "Invalid input", MessageBoxButton.OK);
                res = false;
            }
            StreamReader sr = new StreamReader(DC.PathToMainInputFile);
            string line = sr.ReadLine();
            int len = 0;
            int required = int.Parse(DC.SegmentSize) * 2;
            bool ValidSegSize = false; 
            while (line != null && ValidSegSize == false)
            {
                len += line.Length;
                if (len > required)
                    ValidSegSize = true;

               line = sr.ReadLine();
            }
            sr.Close();
            if(!ValidSegSize)
            {
                MessageBox.Show("File should be at least twice bigger then seg Size", "Invalid input", MessageBoxButton.OK);
                res = false;
            }

            if (res )
            {
                
              
                enginePipe.sendEngineMove("NGRAMSIZE");
                enginePipe.sendEngineMove(DC.NgramSize.ToString());
                enginePipe.sendEngineMove("SEGMENTSIZE");
                enginePipe.sendEngineMove(DC.SegmentSize.ToString());
                enginePipe.sendEngineMove("EXAMINESTOPWORDFILE");
                enginePipe.sendEngineMove(DC.PathToMainInputFile);
                enginePipe.sendEngineMove("EXAMINEPATHFILE");
                enginePipe.sendEngineMove(DC.PathToStopWordsFile);
                enginePipe.sendEngineMove("CHOSENRUN");
                enginePipe.sendEngineMove(DC.ChoosenRun.ToString());
                enginePipe.sendEngineMove("PREFEREDCLUSTERSNUMBER");
                enginePipe.sendEngineMove(DC.ChoosenClustersNumber.ToString());
                enginePipe.sendEngineMove("STARTWORK");
                
                return true;
            }
            else
                return false;
            
        }


        public void connectNewPipe()
        {
           // ConnectionManager.ConnectPlagEnginePipe();
            enginePipe = new Pipe("PlagPipe");
            enginePipe.connect();

        }
        private void AnalyzeTextButton(object sender, RoutedEventArgs e)
        {
            
            if (true == StartBackgroundWork())
            {
                var DC = this.DataContext as MainShellViewModel;
                ConnectionManager.saveData(DC.NgramSize, DC.PathToMainInputFile, DC.SegmentSize, DC.ChoosenRun);
                enginePipe.close();
                
                LoadingWindow LW = new LoadingWindow(this);
         
                this.Hide();
                LW.Show();


            }
            //else
            //{
            //    //pop up error message
            //    MessageBox.Show("Please Fill all fields", "Invalid input", MessageBoxButton.OK);
            //}

        }
        
        public void LoadAgain()
        {
            this.Show();
            enginePipe = new Pipe("PlagPipe");
            enginePipe.connect();
        }
        private void BrowseFileClicked(object sender, RoutedEventArgs e)
        {
            // Create OpenFileDialog 
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();



            // Set filter for file extension and default file extension 
            dlg.DefaultExt = ".txt";
            dlg.Filter = "Text Files (*.txt)|*.txt|All Files (*.*)|*.*";


            // Display OpenFileDialog by calling ShowDialog method 
            Nullable<bool> result = dlg.ShowDialog();


            // Get the selected file name and display in a TextBox 
            if (result == true)
            {

                // Open document 
                string filename = dlg.FileName;

                if (filename.Substring(filename.Length - 4) != ".txt")
                {

                    MessageBox.Show("Please Choose a text File", "Invalid input", MessageBoxButton.OK);
                    return;
                }
                var DC = this.DataContext as MainShellViewModel;

                if ((sender as Button).Name == "FileBrowseStopWordsButton")
                {
                    DC.PathToStopWordsFile = filename;
                    DC.ExaminationStopWordsLabelColor = Brushes.YellowGreen;
                }
                else
                {
                    DC.PathToMainInputFile = filename;
                    DC.ExaminationLabelColor = Brushes.YellowGreen;

                }
            }
        }


        
    private void NumberValidationTextBox(object sender, TextCompositionEventArgs e)
    {
        Regex regex = new Regex("[^0-9]+");
        e.Handled = regex.IsMatch(e.Text);
    }

    private void OnWindowClosing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            enginePipe.sendEngineMove("QUIT");
            enginePipe.getEngineMessage();
        }
    }
}

