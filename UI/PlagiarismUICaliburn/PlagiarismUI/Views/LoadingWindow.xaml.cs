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
        private Window _previousWindow;
        

        public LoadingWindow(Window window )
        {


            InitializeComponent();
            _previousWindow = window;
             DataContext = new LoadingWindowViewModel();


        }

        private void ConnectLoadingPipe_Completed(object sender, RunWorkerCompletedEventArgs e)
        {
            ResultsWindow RW = new ResultsWindow();
            this.Hide();
            RW.ShowDialog();
        }

        private void InitProperties()
        {

        }
        private void backFromLoading_Click(object sender, EventArgs e)
        {

            InitProperties();

            this.Close();
            _previousWindow.Show();
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
        }
    }
}


// Thread.CurrentThread.Priority = ThreadPriority.Highest;
// MethodInvoker myProcessStarter = new MethodInvoker(ConnectLoadingPipe);
// myProcessStarter.BeginInvoke(null, null);
//Thread.CurrentThread.Priority = ThreadPriority.Highest;
//Thread newPipe = new Thread(ConnectLoadingPipe);
//newPipe.Start();

//enginePipe = new Pipe("PIPELOADNAME"); //PIPELOADNAME
//enginePipe.connect();
//UIenginePipe = new Pipe("PIPEUPDATEUI");
//UIenginePipe.connect();
//Thread.CurrentThread.Priority = ThreadPriority.Highest;
//var DC = this.DataContext as LoadingWindowViewModel;
//string state = UIenginePipe.getEngineMessage();
//while (state != "FinishLoadingStage")//TODO change from true
//{
//    state = UIenginePipe.getEngineMessage();
//    switch (state)
//    {
//        case "OmitStopWordsStepFinished":
//            DC.OmitStopWordsStepFinished = Brushes.Blue;
//            //  MessageBox.Show("OmitStopWordsStepFinished");
//            break;
//        case "BuldCFMsStepFinished":
//            DC.BuldCFMsStepFinished = Brushes.Blue;
//            //    MessageBox.Show("BuldCFMsStepFinished");
//            break;
//        case "ExtractNgramsStepFinished":
//            DC.ExtractNgramsStepFinished = Brushes.Blue;
//            //    MessageBox.Show("ExtractNgramsStepFinished");
//            break;
//        case "ExamineResult":
//            DC.ExamineResult = Brushes.Blue;
//            // MessageBox.Show("ExamineResult");
//            break;
//        case "DevideTextToSegStepFinished":
//            DC.DevideTextToSegStepFinished = Brushes.Blue;
//            //  MessageBox.Show("DevideTextToSegStepFinished");
//            break;
//        case "CalcApproxMeasStepFinished":
//            DC.CalcApproxMeasStepFinished = Brushes.Blue;
//            //   MessageBox.Show("DevideTextToSegStepFinished");
//            break;
//        case "BuildSPsStepFinished":
//            DC.BuildSPsStepFinished = Brushes.Blue;
//            //   MessageBox.Show("DevideTextToSegStepFinished");

//            break;
//        case "BuildQsStepFinished":
//            DC.BuildQsStepFinished = Brushes.Blue;
//            //  MessageBox.Show("DevideTextToSegStepFinished");

//            break;
//        case "CalcAQMeasureStepFinished":
//            DC.CalcAQMeasureStepFinished = Brushes.Blue;
//            // MessageBox.Show("DevideTextToSegStepFinished");

//            break;
//        case "BuildVocStepFinished":
//            DC.BuildVocStepFinished = Brushes.Blue;

//            break;
//        //case "FinishLoadingStage":
//        //    e.Cancel = true;
//        //    break;



//        default:
//            break;
//    }


//}
//ResultsWindow RW = new ResultsWindow();
//this.Hide();
//RW.ShowDialog();


//private void UpdateField(string message)
//{
//    var DC = this.DataContext as LoadingWindowViewModel;
//    PropertyInfo propertyInfo = DC.GetType().GetProperty(message);
//    propertyInfo.SetValue(DC, Convert.ChangeType(Brushes.Blue, propertyInfo.PropertyType), null);
//    t = _mevent;
//    t.ObserveOnDispatcher().Subscribe(onUpdate);
//}

//private void onUpdate(Unit unit)
//{

//}

//  public delegate void UpdateTextCallback(string message);object sender, DoWorkEventArgs e