using PlagiarismUI.InfraS;
using System;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Globalization;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Input;
using System.Windows.Media;

namespace PlagiarismUI
{
    public class MainShellViewModel : UserControl, INotifyPropertyChanged
    {



        /*fields*/
        #region Vars
        private string _PathToMainInputFile = "No File Choosen";
        private string _PathToStopWordsFile = "No File Choosen";
        private ObservableCollection<string> _RunSelection = new ObservableCollection<string> { "BOTH", "Clustered","Dynamical"};
        private string _ChoosenRun = "Dynamical";
        private ObservableCollection<string> _PreferedClustersNumberSelection = new ObservableCollection<string> { "Examine in algorithm", "2", "3", "4", "5", "6", "7", "8", "9"};
        private string _ChoosenClustersNumber = "Examine in algorithm";
        private int _StopWordsListChecked=3;
        private int _NgramSize = 3;
        private int _SegmentSize = 40;
        private bool _AnalyzeEnabled = true; //TODO
        private bool _SegmentSizeError = false; 
        private bool _NgramSizeError = false; 
        private bool _NgramGreaterThanSegmentError = false; 
        private bool _StopWordsEnabledCheckBoxChecked = true;
        private bool _ClusteredOrBothRunChecked = false;
        private Brush _ExaminationLabelColor = Brushes.Red;
        private Brush _ExaminationStopWordsLabelColor = Brushes.Red;
        #endregion


        #region Properties
        /*Properties*/
        public Brush ExaminationLabelColor
        {
            get { return _ExaminationLabelColor; }
            set { _ExaminationLabelColor = value; RaisePropertyChanged("ExaminationLabelColor"); }
        }
        public Brush ExaminationStopWordsLabelColor
        {
            get { return _ExaminationStopWordsLabelColor; }
            set { _ExaminationStopWordsLabelColor = value; RaisePropertyChanged("ExaminationStopWordsLabelColor"); }
        }





        public bool AnalyzeEnabled
        {
            get { return _AnalyzeEnabled; }
            set { _AnalyzeEnabled = value; RaisePropertyChanged("AnalyzeEnabled"); }
        }
        public string SegmentSize
        {
            get
            {
                return _SegmentSize.ToString();
            }
            set
            {
                int res = int.Parse(value);
                if (res > 11)
                {
                    _SegmentSize = res;
                    RaisePropertyChanged("SegmentSize");
                    SegmentSizeError = false;
                }
                else
                {
                    SegmentSizeError = true;
                }
                
            }
        }
        public bool SegmentSizeError
        {
            get
            {
                return _SegmentSizeError;
            }
            set
            {
                _SegmentSizeError = value;
                RaisePropertyChanged("SegmentSizeError");
            }
        }
        public string NgramSize
        {
            get
            {
                return _NgramSize.ToString();
            }
            set
            {
                int NgramRes = int.Parse(value);
                int SegmentRes = int.Parse(SegmentSize);
                if (NgramRes > 2 && NgramRes < SegmentRes)
                {
                    _NgramSize = NgramRes;
                    RaisePropertyChanged("NgramSize");
                    NgramSizeError = false;
                    NgramGreaterThanSegmentError = false;
                }
                else
                {
                    if (NgramRes <= 2)
                    {
                        NgramGreaterThanSegmentError = false;
                        NgramSizeError = true;
                    }
                    else
                    {
                        NgramSizeError = false;
                        NgramGreaterThanSegmentError = true;
                    }
                }
            }
        }
        public bool NgramSizeError
        {
            get
            {
                return _NgramSizeError;
            }
            set
            {
                _NgramSizeError = value;
                RaisePropertyChanged("NgramSizeError");
            }
        }
        public bool NgramGreaterThanSegmentError
        {
            get
            {
                return _NgramGreaterThanSegmentError;
            }
            set
            {
                _NgramGreaterThanSegmentError = value;
                RaisePropertyChanged("NgramGreaterThanSegmentError");
            }
        }

        public bool StopWordsEnabledCheckBoxChecked
        {
            get { return _StopWordsEnabledCheckBoxChecked; }
            set
            {
                _StopWordsEnabledCheckBoxChecked = value;
                RaisePropertyChanged("StopWordsEnabledCheckBoxChecked");
                if (value == false)
                    PathToStopWordsFile = "EMPTY";
                else
                    PathToStopWordsFile = "No File Choosen";
            }
        }
        public int StopWordsListChecked
        {
            get { return _StopWordsListChecked; }
            set {
                    _StopWordsListChecked = value;
                    RaisePropertyChanged("StopWordsListChecked");
                if (value == 1)
                    PathToStopWordsFile = "ACADEMIC";
                if (value == 2)
                    PathToStopWordsFile = "LITERATURE";
                if (value == 3)
                    PathToStopWordsFile = "No File Choosen";
            }
        }
        public string ChoosenRun
        {
            get { return _ChoosenRun; }
            set {
                    _ChoosenRun = value;
                    if (value == "Clustered" || value == "BOTH")
                    {
                        ClusteredOrBothRunChecked = true;
                    }
                    else
                    {
                        ClusteredOrBothRunChecked = false;
                    }
                }
        }
        public string ChoosenClustersNumber
        {
            get { return _ChoosenClustersNumber; }
            set { _ChoosenClustersNumber = value; }
        }

        public bool ClusteredOrBothRunChecked
        {
            get { return _ClusteredOrBothRunChecked; }
            set
            {
                _ClusteredOrBothRunChecked = value;
                RaisePropertyChanged("ClusteredOrBothRunChecked");
            }
        }
        public ObservableCollection<string> RunSelection
        {
            get
            {
                return _RunSelection;
            }
        }
        public ObservableCollection<string> PreferedClustersNumberSelection
        {
            get
            {
                return _PreferedClustersNumberSelection;
            }
        }
        
        public string PathToStopWordsFile
        {
            get { return _PathToStopWordsFile; }
            set { _PathToStopWordsFile = value; RaisePropertyChanged("PathToStopWordsFile"); }
        }
        public string PathToMainInputFile
        {
            get
            {
                return _PathToMainInputFile;
            }
            set
            {
                _PathToMainInputFile = value; RaisePropertyChanged("PathToMainInputFile");
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




    public class RadioBoolToIntConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            int integer = (int)value;
            if (integer == int.Parse(parameter.ToString()))
                return true;
            else
                return false;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            return parameter;
        }
    }

    class MultiBooleanToVisibilityConverter : IMultiValueConverter
    {
        public object Convert(object[] values,
                                Type targetType,
                                object parameter,
                                System.Globalization.CultureInfo culture)
        {
            bool visible = true;
            foreach (object value in values)
                if (value is bool)
                    visible = visible && (bool)value;

            if (visible)
                return System.Windows.Visibility.Visible;
            else
                return System.Windows.Visibility.Hidden;
        }

        public object[] ConvertBack(object value,
                                    Type[] targetTypes,
                                    object parameter,
                                    System.Globalization.CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}