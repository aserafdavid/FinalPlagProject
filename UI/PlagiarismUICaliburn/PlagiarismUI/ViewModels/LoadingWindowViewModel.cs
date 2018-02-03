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
                        OmitStopWordsStepFinished = Brushes.GreenYellow;
                        OmitStopWordsStepFinishedText = Brushes.Black;
                        //ShowResults = true;
                        //return;
                        break;
                    case "DevideTextToSegStepFinished":
                        OmitStopWordsStepFinished   = Brushes.GreenYellow;
                        DevideTextToSegStepFinished = Brushes.GreenYellow;
                        OmitStopWordsStepFinishedText = Brushes.Black;
                        DevideTextToSegStepFinishedText = Brushes.Black;
                        break;
                    case "ExtractNgramsStepFinished":
                        OmitStopWordsStepFinished =   Brushes.GreenYellow;
                        DevideTextToSegStepFinished = Brushes.GreenYellow;
                        ExtractNgramsStepFinished =   Brushes.GreenYellow;
                        OmitStopWordsStepFinishedText = Brushes.Black;
                        DevideTextToSegStepFinishedText = Brushes.Black;
                        ExtractNgramsStepFinishedText = Brushes.Black;
                        break;
                    case "BuildVocStepFinished":
                        OmitStopWordsStepFinished =   Brushes.GreenYellow;
                        DevideTextToSegStepFinished = Brushes.GreenYellow;
                        ExtractNgramsStepFinished =   Brushes.GreenYellow;
                        BuildVocStepFinished =        Brushes.GreenYellow;
                        OmitStopWordsStepFinishedText = Brushes.Black;
                        DevideTextToSegStepFinishedText = Brushes.Black;
                        ExtractNgramsStepFinishedText = Brushes.Black;
                        BuildVocStepFinishedText = Brushes.Black;
                        break;
                    case "BuldCFMsStepFinished":
                        OmitStopWordsStepFinished = Brushes.GreenYellow;
                        DevideTextToSegStepFinished = Brushes.GreenYellow;
                        ExtractNgramsStepFinished = Brushes.GreenYellow;
                        BuildVocStepFinished = Brushes.GreenYellow;
                        BuldCFMsStepFinished = Brushes.GreenYellow;
                        OmitStopWordsStepFinishedText = Brushes.Black;
                        DevideTextToSegStepFinishedText = Brushes.Black;
                        ExtractNgramsStepFinishedText = Brushes.Black;
                        BuildVocStepFinishedText = Brushes.Black;
                        BuldCFMsStepFinishedText = Brushes.Black;
                        break;

                    case "BuildSPsStepFinished":
                        OmitStopWordsStepFinished = Brushes.GreenYellow;
                        DevideTextToSegStepFinished = Brushes.GreenYellow;
                        ExtractNgramsStepFinished = Brushes.GreenYellow;
                        BuildVocStepFinished = Brushes.GreenYellow;
                        BuldCFMsStepFinished = Brushes.GreenYellow;
                        BuildSPsStepFinished = Brushes.GreenYellow;

                        OmitStopWordsStepFinishedText = Brushes.Black;
                        DevideTextToSegStepFinishedText = Brushes.Black;
                        ExtractNgramsStepFinishedText = Brushes.Black;
                        BuildVocStepFinishedText= Brushes.Black;
                        BuldCFMsStepFinishedText= Brushes.Black;
                        BuildSPsStepFinishedText= Brushes.Black;
                        break;


                    case "BuildQsStepFinished":
                        OmitStopWordsStepFinished = Brushes.GreenYellow;
                        DevideTextToSegStepFinished = Brushes.GreenYellow;
                        ExtractNgramsStepFinished = Brushes.GreenYellow;
                        BuildVocStepFinished = Brushes.GreenYellow;
                        BuldCFMsStepFinished = Brushes.GreenYellow;
                        BuildSPsStepFinished = Brushes.GreenYellow;
                        BuildQsStepFinished = Brushes.GreenYellow;

                        OmitStopWordsStepFinishedText = Brushes.Black;
                        DevideTextToSegStepFinishedText = Brushes.Black;
                        ExtractNgramsStepFinishedText = Brushes.Black;
                        BuildVocStepFinishedText = Brushes.Black;
                        BuldCFMsStepFinishedText = Brushes.Black;
                        BuildSPsStepFinishedText = Brushes.Black;
                        BuildQsStepFinishedText = Brushes.Black;
                        break;

                    case "CalcAQMeasureStepFinished":
                        OmitStopWordsStepFinished = Brushes.GreenYellow;
                        DevideTextToSegStepFinished = Brushes.GreenYellow;
                        ExtractNgramsStepFinished = Brushes.GreenYellow;
                        BuildVocStepFinished = Brushes.GreenYellow;
                        BuldCFMsStepFinished = Brushes.GreenYellow;
                        BuildSPsStepFinished = Brushes.GreenYellow;
                        BuildQsStepFinished = Brushes.GreenYellow;
                        CalcAQMeasureStepFinished = Brushes.GreenYellow;

                        OmitStopWordsStepFinishedText = Brushes.Black;
                        DevideTextToSegStepFinishedText = Brushes.Black;
                        ExtractNgramsStepFinishedText = Brushes.Black;
                        BuildVocStepFinishedText = Brushes.Black;
                        BuldCFMsStepFinishedText = Brushes.Black;
                        BuildSPsStepFinishedText = Brushes.Black;
                        BuildQsStepFinishedText = Brushes.Black;
                        CalcAQMeasureStepFinishedText = Brushes.Black;

                        break;
                    case "CalcApproxMeasStepFinished":
                        OmitStopWordsStepFinished = Brushes.GreenYellow;
                        DevideTextToSegStepFinished = Brushes.GreenYellow;
                        ExtractNgramsStepFinished = Brushes.GreenYellow;
                        BuildVocStepFinished = Brushes.GreenYellow;
                        BuldCFMsStepFinished = Brushes.GreenYellow;
                        BuildSPsStepFinished = Brushes.GreenYellow;
                        BuildQsStepFinished = Brushes.GreenYellow;
                        CalcAQMeasureStepFinished = Brushes.GreenYellow;      
                        CalcApproxMeasStepFinished = Brushes.GreenYellow;

                        OmitStopWordsStepFinishedText = Brushes.Black;
                        DevideTextToSegStepFinishedText = Brushes.Black;
                        ExtractNgramsStepFinishedText = Brushes.Black;
                        BuldCFMsStepFinishedText= Brushes.Black;
                        BuildSPsStepFinishedText= Brushes.Black;
                        BuildVocStepFinishedText = Brushes.Black;
                        BuildQsStepFinishedText = Brushes.Black;
                        CalcAQMeasureStepFinishedText = Brushes.Black;
                        CalcApproxMeasStepFinishedText = Brushes.Black;
                        break;                                                
                    case "ExamineResult":                                     
                        OmitStopWordsStepFinished = Brushes.GreenYellow;      
                        DevideTextToSegStepFinished = Brushes.GreenYellow;    
                        ExtractNgramsStepFinished = Brushes.GreenYellow;      
                        BuildVocStepFinished =  Brushes.GreenYellow;           
                        BuldCFMsStepFinished = Brushes.GreenYellow;           
                        BuildSPsStepFinished = Brushes.GreenYellow;
                        BuildQsStepFinished = Brushes.GreenYellow;
                        CalcAQMeasureStepFinished = Brushes.GreenYellow;
                        CalcApproxMeasStepFinished = Brushes.GreenYellow;
                        ExamineResult = Brushes.GreenYellow;

                        OmitStopWordsStepFinishedText = Brushes.Black;
                        DevideTextToSegStepFinishedText = Brushes.Black;
                        ExtractNgramsStepFinishedText = Brushes.Black;
                        BuildVocStepFinishedText = Brushes.Black;
                        BuldCFMsStepFinishedText = Brushes.Black;
                        BuildSPsStepFinishedText = Brushes.Black;
                        BuildQsStepFinishedText = Brushes.Black;
                        CalcAQMeasureStepFinishedText = Brushes.Black;
                        CalcApproxMeasStepFinishedText = Brushes.Black;
                        ExamineResultText = Brushes.Black;
                        break;


                    case "EvmCreationFinished":
                        OmitStopWordsStepFinished = Brushes.GreenYellow;
                        DevideTextToSegStepFinished = Brushes.GreenYellow;
                        ExtractNgramsStepFinished = Brushes.GreenYellow;
                        BuildVocStepFinished = Brushes.GreenYellow;
                        BuldCFMsStepFinished = Brushes.GreenYellow;
                        BuildSPsStepFinished = Brushes.GreenYellow;
                        EvmCreationFinished = Brushes.GreenYellow;

                        OmitStopWordsStepFinishedText = Brushes.Black;
                        DevideTextToSegStepFinishedText = Brushes.Black;
                        ExtractNgramsStepFinishedText = Brushes.Black;
                        BuildVocStepFinishedText = Brushes.Black;
                        BuldCFMsStepFinishedText = Brushes.Black;
                        BuildSPsStepFinishedText = Brushes.Black;
                        EvmCreationFinishedText = Brushes.Black;
                        break;
                    case "ClusterizationFinished":
                        OmitStopWordsStepFinished = Brushes.GreenYellow;
                        DevideTextToSegStepFinished = Brushes.GreenYellow;
                        ExtractNgramsStepFinished = Brushes.GreenYellow;
                        BuildVocStepFinished = Brushes.GreenYellow;
                        BuldCFMsStepFinished = Brushes.GreenYellow;
                        BuildSPsStepFinished = Brushes.GreenYellow;
                        EvmCreationFinished = Brushes.GreenYellow;
                        ClusterizationFinished = Brushes.GreenYellow;


                        OmitStopWordsStepFinishedText = Brushes.Black;
                        DevideTextToSegStepFinishedText = Brushes.Black;
                        ExtractNgramsStepFinishedText = Brushes.Black;
                        BuildVocStepFinishedText = Brushes.Black;
                        BuldCFMsStepFinishedText = Brushes.Black;
                        BuildSPsStepFinishedText = Brushes.Black;
                        EvmCreationFinishedText = Brushes.Black;
                        ClusterizationFinishedText = Brushes.Black;
                        break;
                    case "ExamineCLResult":
                        OmitStopWordsStepFinished = Brushes.GreenYellow;
                        DevideTextToSegStepFinished = Brushes.GreenYellow;
                        ExtractNgramsStepFinished = Brushes.GreenYellow;
                        BuildVocStepFinished = Brushes.GreenYellow;
                        BuldCFMsStepFinished = Brushes.GreenYellow;
                        BuildSPsStepFinished = Brushes.GreenYellow;
                        EvmCreationFinished = Brushes.GreenYellow;
                        ClusterizationFinished = Brushes.GreenYellow;
                        ExamineCLResult = Brushes.GreenYellow;

                        OmitStopWordsStepFinishedText = Brushes.Black;
                        DevideTextToSegStepFinishedText = Brushes.Black;
                        ExtractNgramsStepFinishedText = Brushes.Black;
                        BuildVocStepFinishedText = Brushes.Black;
                        BuldCFMsStepFinishedText = Brushes.Black;
                        BuildSPsStepFinishedText = Brushes.Black;
                        EvmCreationFinishedText = Brushes.Black;
                        ClusterizationFinishedText = Brushes.Black;
                        ExamineCLResultText = Brushes.Black;
                        break;


                    case "FinishLoadingStage":
                        {
                            string ResPath;
                            
                            ResPath = ConnectionManager.GetUIengineMessage();
                            while (ResPath == "")
                                ResPath = ConnectionManager.GetUIengineMessage();


                            ConnectionManager.GetUIenginePipe().sendEngineMove("ACCEPTED");
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
        private Brush _OmitStopWordsStepFinishedText = Brushes.White;
        private Brush _DevideTextToSegStepFinishedText = Brushes.White;
        private Brush _ExtractNgramsStepFinishedText = Brushes.White;
        private Brush _BuildVocStepFinishedText = Brushes.White;
        private Brush _BuldCFMsStepFinishedText = Brushes.White;
        private Brush _BuildSPsStepFinishedText = Brushes.White;

        private Brush _BuildQsStepFinishedText = Brushes.White;
        private Brush _CalcAQMeasureStepFinishedText = Brushes.White;
        private Brush _CalcApproxMeasStepFinishedText = Brushes.White;
        private Brush _ExamineResultText = Brushes.White;

        private Brush _EvmCreationFinishedText = Brushes.White;
        private Brush _ClusterizationFinishedText = Brushes.White;
        private Brush _ExamineCLResultText = Brushes.White;

        //GreenYellow
        private Brush _OmitStopWordsStepFinished = Brushes.Black;
        private Brush _DevideTextToSegStepFinished = Brushes.Black;
        private Brush _ExtractNgramsStepFinished = Brushes.Black;
        private Brush _BuildVocStepFinished = Brushes.Black;
        private Brush _BuldCFMsStepFinished = Brushes.Black;
        private Brush _BuildSPsStepFinished = Brushes.Black;

        private Brush _BuildQsStepFinished = Brushes.Black;
        private Brush _CalcAQMeasureStepFinished = Brushes.Black;
        private Brush _CalcApproxMeasStepFinished = Brushes.Black;
        private Brush _ExamineResult = Brushes.Black;

        private Brush _EvmCreationFinished = Brushes.Black;
        private Brush _ClusterizationFinished = Brushes.Black;
        private Brush _ExamineCLResult = Brushes.Black;

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
        public Brush EvmCreationFinishedText
        {
            get
            {
                return _EvmCreationFinishedText;
            }
            set
            {
                _EvmCreationFinishedText = value;
                RaisePropertyChanged("EvmCreationFinishedText");
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
        public Brush ClusterizationFinishedText
        {
            get
            {
                return _ClusterizationFinishedText;
            }
            set
            {
                _ClusterizationFinishedText = value;
                RaisePropertyChanged("ClusterizationFinishedText");
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
        public Brush ExamineCLResultText
        {
            get
            {
                return _ExamineCLResultText;
            }
            set
            {
                _ExamineCLResultText = value;
                RaisePropertyChanged("ExamineCLResultText");
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
        public Brush OmitStopWordsStepFinishedText
        {
            get
            {
                return _OmitStopWordsStepFinishedText;
            }
            set
            {
                _OmitStopWordsStepFinishedText = value;
                RaisePropertyChanged("OmitStopWordsStepFinishedText");
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
        public Brush BuldCFMsStepFinishedText
        {
            get
            {
                return _BuldCFMsStepFinishedText;
            }
            set
            {
                _BuldCFMsStepFinishedText = value;
                RaisePropertyChanged("BuldCFMsStepFinishedText");
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
        public Brush ExtractNgramsStepFinishedText
        {
            get
            {
                return _ExtractNgramsStepFinishedText;
            }
            set
            {
                _ExtractNgramsStepFinishedText = value;
                RaisePropertyChanged("ExtractNgramsStepFinishedText");
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
        public Brush ExamineResultText
        {
            get
            {
                return _ExamineResultText;
            }
            set
            {
                _ExamineResultText = value;
                RaisePropertyChanged("ExamineResultText");
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
        public Brush DevideTextToSegStepFinishedText
        {
            get
            {
                return _DevideTextToSegStepFinishedText;
            }
            set
            {
                _DevideTextToSegStepFinishedText = value;
                RaisePropertyChanged("DevideTextToSegStepFinishedText");
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
        public Brush CalcApproxMeasStepFinishedText
        {
            get
            {
                return _CalcApproxMeasStepFinishedText;
            }
            set
            {
                _CalcApproxMeasStepFinishedText = value;
                RaisePropertyChanged("CalcApproxMeasStepFinishedText");
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

        public Brush BuildSPsStepFinishedText
        {
            get
            {
                return _BuildSPsStepFinishedText;
            }
            set
            {
                _BuildSPsStepFinishedText = value;
                RaisePropertyChanged("BuildSPsStepFinishedText");
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
        public Brush BuildQsStepFinishedText
        {
            get
            {
                return _BuildQsStepFinishedText;
            }
            set
            {
                _BuildQsStepFinishedText = value;
                RaisePropertyChanged("BuildQsStepFinishedText");
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
        public Brush CalcAQMeasureStepFinishedText
        {
            get
            {
                return _CalcAQMeasureStepFinishedText;
            }
            set
            {
                _CalcAQMeasureStepFinishedText = value;
                RaisePropertyChanged("CalcAQMeasureStepFinishedText");
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
        public Brush BuildVocStepFinishedText
        {
            get
            {
                return _BuildVocStepFinishedText;
            }
            set
            {
                _BuildVocStepFinishedText = value;
                RaisePropertyChanged("BuildVocStepFinishedText");
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




