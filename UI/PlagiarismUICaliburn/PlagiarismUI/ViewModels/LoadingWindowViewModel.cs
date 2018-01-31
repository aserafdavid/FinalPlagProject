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
                        OmitStopWordsStepFinished = Brushes.Blue;
                        DevideTextToSegStepFinished = Brushes.Blue;
                        break;
                    case "ExtractNgramsStepFinished":
                        OmitStopWordsStepFinished = Brushes.Blue;
                        DevideTextToSegStepFinished = Brushes.Blue;
                        ExtractNgramsStepFinished = Brushes.Blue;
                        break;
                    case "BuildVocStepFinished":
                        OmitStopWordsStepFinished = Brushes.Blue;
                        DevideTextToSegStepFinished = Brushes.Blue;
                        ExtractNgramsStepFinished = Brushes.Blue;
                        BuildVocStepFinished = Brushes.Blue;
                        break;
                    case "BuldCFMsStepFinished":
                        OmitStopWordsStepFinished = Brushes.Blue;
                        DevideTextToSegStepFinished = Brushes.Blue;
                        ExtractNgramsStepFinished = Brushes.Blue;
                        BuildVocStepFinished = Brushes.Blue;
                        BuldCFMsStepFinished = Brushes.Blue;
                        break;
                    case "BuildSPsStepFinished":
                        OmitStopWordsStepFinished = Brushes.Blue;
                        DevideTextToSegStepFinished = Brushes.Blue;
                        ExtractNgramsStepFinished = Brushes.Blue;
                        BuildVocStepFinished = Brushes.Blue;
                        BuldCFMsStepFinished = Brushes.Blue;
                        BuildSPsStepFinished = Brushes.Blue;
                        break;


                    case "BuildQsStepFinished":
                        OmitStopWordsStepFinished = Brushes.Blue;
                        DevideTextToSegStepFinished = Brushes.Blue;
                        ExtractNgramsStepFinished = Brushes.Blue;
                        BuildVocStepFinished = Brushes.Blue;
                        BuldCFMsStepFinished = Brushes.Blue;
                        BuildSPsStepFinished = Brushes.Blue;
                        BuildQsStepFinished = Brushes.Blue;
                        break;
                    case "CalcAQMeasureStepFinished":
                        OmitStopWordsStepFinished = Brushes.Blue;
                        DevideTextToSegStepFinished = Brushes.Blue;
                        ExtractNgramsStepFinished = Brushes.Blue;
                        BuildVocStepFinished = Brushes.Blue;
                        BuldCFMsStepFinished = Brushes.Blue;
                        BuildSPsStepFinished = Brushes.Blue;
                        BuildQsStepFinished = Brushes.Blue;
                        CalcAQMeasureStepFinished = Brushes.Blue;
                        break;
                    case "CalcApproxMeasStepFinished":
                        OmitStopWordsStepFinished = Brushes.Blue;
                        DevideTextToSegStepFinished = Brushes.Blue;
                        ExtractNgramsStepFinished = Brushes.Blue;
                        BuildVocStepFinished = Brushes.Blue;
                        BuldCFMsStepFinished = Brushes.Blue;
                        BuildSPsStepFinished = Brushes.Blue;
                        BuildQsStepFinished = Brushes.Blue;
                        CalcAQMeasureStepFinished = Brushes.Blue;
                        CalcApproxMeasStepFinished = Brushes.Blue;
                        break;
                    case "ExamineResult":
                        OmitStopWordsStepFinished = Brushes.Blue;
                        DevideTextToSegStepFinished = Brushes.Blue;
                        ExtractNgramsStepFinished = Brushes.Blue;
                        BuildVocStepFinished = Brushes.Blue;
                        BuldCFMsStepFinished = Brushes.Blue;
                        BuildSPsStepFinished = Brushes.Blue;
                        BuildQsStepFinished = Brushes.Blue;
                        CalcAQMeasureStepFinished = Brushes.Blue;
                        CalcApproxMeasStepFinished = Brushes.Blue;
                        ExamineResult = Brushes.Blue;
                        break;


                    case "EvmCreationFinished":
                        OmitStopWordsStepFinished = Brushes.Blue;
                        DevideTextToSegStepFinished = Brushes.Blue;
                        ExtractNgramsStepFinished = Brushes.Blue;
                        BuildVocStepFinished = Brushes.Blue;
                        BuldCFMsStepFinished = Brushes.Blue;
                        BuildSPsStepFinished = Brushes.Blue;
                        EvmCreationFinished = Brushes.Blue;
                        break;
                    case "ClusterizationFinished":
                        OmitStopWordsStepFinished = Brushes.Blue;
                        DevideTextToSegStepFinished = Brushes.Blue;
                        ExtractNgramsStepFinished = Brushes.Blue;
                        BuildVocStepFinished = Brushes.Blue;
                        BuldCFMsStepFinished = Brushes.Blue;
                        BuildSPsStepFinished = Brushes.Blue;
                        EvmCreationFinished = Brushes.Blue;
                        ClusterizationFinished = Brushes.Blue;
                        break;
                    case "ExamineCLResult":
                        OmitStopWordsStepFinished = Brushes.Blue;
                        DevideTextToSegStepFinished = Brushes.Blue;
                        ExtractNgramsStepFinished = Brushes.Blue;
                        BuildVocStepFinished = Brushes.Blue;
                        BuldCFMsStepFinished = Brushes.Blue;
                        BuildSPsStepFinished = Brushes.Blue;
                        EvmCreationFinished = Brushes.Blue;
                        ClusterizationFinished = Brushes.Blue;
                        ExamineCLResult = Brushes.Blue;
                        break;


                    case "FinishLoadingStage":
                        {
                            string ResPath;
                            
                            ResPath = ConnectionManager.GetUIengineMessage();
                            while (ResPath == "")
                                ResPath = ConnectionManager.GetUIengineMessage();


                            ConnectionManager.GetUIenginePipe().sendEngineMove("ACCEPTED");
                            //TODODAVID ResultPath
                            ResultPath = ResPath;
                            ShowResults = true;
                            return;
                        }


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
        private Brush _DevideTextToSegStepFinished = Brushes.White;
        private Brush _ExtractNgramsStepFinished = Brushes.White;
        private Brush _BuildVocStepFinished = Brushes.White;
        private Brush _BuldCFMsStepFinished = Brushes.White;
        private Brush _BuildSPsStepFinished = Brushes.White;

        private Brush _BuildQsStepFinished = Brushes.White;
        private Brush _CalcAQMeasureStepFinished = Brushes.White;
        private Brush _CalcApproxMeasStepFinished = Brushes.White;
        private Brush _ExamineResult = Brushes.White;

        private Brush _EvmCreationFinished = Brushes.White;
        private Brush _ClusterizationFinished = Brushes.White;
        private Brush _ExamineCLResult = Brushes.White;

        private bool _ShowResults = false;


        #region properties

        public bool ShowResults
        {
            get { return _ShowResults; }
            set { _ShowResults = value; RaisePropertyChanged("ShowResults"); }
        }

        public static volatile string ResultPath = "";

        public string GETResultPath()
        {
            return ResultPath;
        }

        public Brush EvmCreationFinished
        {
            get
            {
                return _EvmCreationFinished;
            }
            set
            {
                _EvmCreationFinished = value;
                RaisePropertyChanged("EvmCreationFinished");
            }
        }
        public Brush ClusterizationFinished
        {
            get
            {
                return _ClusterizationFinished;
            }
            set
            {
                _ClusterizationFinished = value;
                RaisePropertyChanged("ClusterizationFinished");
            }
        }
        public Brush ExamineCLResult
        {
            get
            {
                return _ExamineCLResult;
            }
            set
            {
                _ExamineCLResult = value;
                RaisePropertyChanged("ExamineCLResult");
            }
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




