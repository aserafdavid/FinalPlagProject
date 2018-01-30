using PlagiarismUI.InfraS;
using PlagiarismUI.Views;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Media;

namespace PlagiarismUI.ViewModels
{
    class LoadingWindowViewModel : UserControl, INotifyPropertyChanged
    {



        private void ConnectLoadingPipe()
        {
            ConnectionManager.ConnectEnginePipe();
            ConnectionManager.ConnectUIenginePipe();
            while (true)//TODO change from true
            {

                string state = ConnectionManager.GetUIengineMessage();
                switch (state)
                {

                    case "OmitStopWordsStepFinished":
                        OmitStopWordsStepFinished = Brushes.Blue;
                        //ShowResults = true;
                        //return;
                        break;

                    case "DevideTextToSegStepFinished":
                        DevideTextToSegStepFinished = Brushes.Blue;
                        break;

                    case "ExtractNgramsStepFinished":
                        ExtractNgramsStepFinished = Brushes.Blue;
                        break;

                    case "BuildVocStepFinished":
                        BuildVocStepFinished = Brushes.Blue;
                        break;

                    case "BuldCFMsStepFinished":
                        BuldCFMsStepFinished = Brushes.Blue;
                        break;

                    case "BuildSPsStepFinished":
                        BuildSPsStepFinished = Brushes.Blue;
                        break;

                    case "BuildQsStepFinished":
                        BuildQsStepFinished = Brushes.Blue;
                        break;

                    case "CalcAQMeasureStepFinished":
                        CalcAQMeasureStepFinished = Brushes.Blue;
                        break;

                    case "CalcApproxMeasStepFinished":
                        CalcApproxMeasStepFinished = Brushes.Blue;
                        break;

                    case "ExamineResult":
                        ExamineResult = Brushes.Blue;
                        break;

                    case "FinishLoadingStage":                        
                        return;


                    case "CancelRUN":                        
                        break;

                    default:
                        break;
                }
            }
        }

        static Thread newPipe;

        public LoadingWindowViewModel()
        {
            newPipe = new Thread(ConnectLoadingPipe);
        //    newPipe.SetApartmentState(ApartmentState.STA);
            newPipe.Start();
            


        }

        private Brush _OmitStopWordsStepFinished = Brushes.White;
        private Brush _BuldCFMsStepFinished = Brushes.White;
        private Brush _ExtractNgramsStepFinished = Brushes.White;
        private Brush _ExamineResult = Brushes.White;
        private Brush _DevideTextToSegStepFinished = Brushes.White;
        private Brush _CalcApproxMeasStepFinished = Brushes.White;
        private Brush _BuildSPsStepFinished = Brushes.White;
        private Brush _BuildQsStepFinished = Brushes.White;
        private Brush _CalcAQMeasureStepFinished = Brushes.White;
        private Brush _BuildVocStepFinished = Brushes.White;

        private bool _ShowResults = false;


        #region properties

        public bool ShowResults
        {
            get { return _ShowResults; }
            set { _ShowResults = value; RaisePropertyChanged("ShowResults"); }
        }

        public Brush OmitStopWordsStepFinished
        {
            get
            {
                return _OmitStopWordsStepFinished;
            }
            set
            {
                _OmitStopWordsStepFinished = value;
                RaisePropertyChanged("OmitStopWordsStepFinished");
            }
        }
        public Brush BuldCFMsStepFinished
        {
            get
            {
                return _BuldCFMsStepFinished;
            }
            set
            {
                _BuldCFMsStepFinished = value;
                RaisePropertyChanged("BuldCFMsStepFinished");
            }
        }
        public Brush ExtractNgramsStepFinished
        {
            get
            {
                return _ExtractNgramsStepFinished;
            }
            set
            {
                _ExtractNgramsStepFinished = value;
                RaisePropertyChanged("ExtractNgramsStepFinished");
            }
        }
        public Brush ExamineResult
        {
            get
            {
                return _ExamineResult;
            }
            set
            {
                _ExamineResult = value;
                RaisePropertyChanged("ExamineResult");
            }
        }
        public Brush DevideTextToSegStepFinished
        {
            get
            {
                return _DevideTextToSegStepFinished;
            }
            set
            {
                _DevideTextToSegStepFinished = value;
                RaisePropertyChanged("DevideTextToSegStepFinished");
            }
        }
        public Brush CalcApproxMeasStepFinished
        {
            get
            {
                return _CalcApproxMeasStepFinished;
            }
            set
            {
                _CalcApproxMeasStepFinished = value;
                RaisePropertyChanged("CalcApproxMeasStepFinished");
            }
        }
        public Brush BuildSPsStepFinished
        {
            get
            {
                return _BuildSPsStepFinished;
            }
            set
            {
                _BuildSPsStepFinished = value;
                RaisePropertyChanged("BuildSPsStepFinished");
            }
        }
        public Brush BuildQsStepFinished
        {
            get
            {
                return _BuildQsStepFinished;
            }
            set
            {
                _BuildQsStepFinished = value;
                RaisePropertyChanged("BuildQsStepFinished");
            }
        }
        public Brush CalcAQMeasureStepFinished
        {
            get
            {
                return _CalcAQMeasureStepFinished;
            }
            set
            {
                _CalcAQMeasureStepFinished = value;
                RaisePropertyChanged("CalcAQMeasureStepFinished");
            }
        }
        public Brush BuildVocStepFinished
        {
            get
            {
                return _BuildVocStepFinished;
            }
            set
            {
                _BuildVocStepFinished = value;
                RaisePropertyChanged("BuildVocStepFinished");
            }
        }

        #endregion
        public event PropertyChangedEventHandler PropertyChanged;
        protected void RaisePropertyChanged(string propertyName)
        {
            var handler = PropertyChanged;
            if (handler != null)
            {
                handler(this, new PropertyChangedEventArgs(propertyName));
            }
        }
    }
}




