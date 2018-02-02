using PlagiarismUI.InfraS;
using PlagiarismUI.ViewModels;
using System;
using System.ComponentModel;
using System.Windows;

namespace PlagiarismUI.Views
{
    public partial class LoadingWindow : Window
    {
        private Window  _previousWindow;
        static bool XClicked = true;

        public LoadingWindow(Window window )
        {


            InitializeComponent();
            _previousWindow =  window;
             DataContext = new LoadingWindowViewModel();
           

        }

        private void ConnectLoadingPipe_Completed(object sender, RunWorkerCompletedEventArgs e)
        {

        }


        private void backFromLoading_Click(object sender, EventArgs e)
        {
            

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
            this.Close();
            MV.Show();
            //  MV.LoadAgain();

        }

        private void ShowResults_Click(object sender, RoutedEventArgs e)
        {
            var DC = this.DataContext as LoadingWindowViewModel;
            string ResultPATH = DC.GETResultPath() ;
            XClicked = false;
            this.Close();
            ResultsWindow RW = new ResultsWindow(_previousWindow , ResultPATH);
            
            RW.ShowDialog();
            
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


