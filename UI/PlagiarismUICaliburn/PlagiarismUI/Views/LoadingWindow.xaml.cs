using PlagiarismUI.InfraS;
using PlagiarismUI.ViewModels;
using System;
using System.ComponentModel;
using System.Windows;

namespace PlagiarismUI.Views
{
    /// <summary>
    /// Interaction logic for LoadingWindow.xaml
    /// </summary>
    public partial class LoadingWindow : Window
    {
        private Window  _previousWindow;
        

        public LoadingWindow(Window window )
        {


            InitializeComponent();
            _previousWindow =  window;
             DataContext = new LoadingWindowViewModel();
           

        }

        private void ConnectLoadingPipe_Completed(object sender, RunWorkerCompletedEventArgs e)
        {

        }

        private void InitProperties()
        {

        }
        private void backFromLoading_Click(object sender, EventArgs e)
        {

            InitProperties();

            this.Close();
            

            //this.Hide();
            var DC = this.DataContext as LoadingWindowViewModel;
            ConnectionManager.GetEnginePipe().sendEngineMove("CANCELRUN");
            string s = ConnectionManager.GetEnginePipe().getEngineMessage();
            if (s == "ACCEPTED")
            {
                ConnectionManager.GetEnginePipe().close();
                ConnectionManager.GetUIenginePipe().close();

            }
            else
            {
                //TODO add popup window
            }
            MainShellView MV = _previousWindow as MainShellView;
            MV.LoadAgain();
        }

        private void ShowResults_Click(object sender, RoutedEventArgs e)
        {
            var DC = this.DataContext as LoadingWindowViewModel;
            string ResultPATH = DC.GETResultPath() ; 
            this.Close();
            ResultsWindow RW = new ResultsWindow(_previousWindow , ResultPATH);
            
            RW.ShowDialog();
            
        }
    }
}

