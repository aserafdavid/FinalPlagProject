using PlagiarismUI.InfraS;
using System;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Globalization;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Input;

namespace PlagiarismUI
{
    public class MainShellViewModel : UserControl, INotifyPropertyChanged
    {



        /*fields*/
        #region Vars
        saveData sd;
        private string _PathToMainInputFile = "No File Choosen";
        private string _PathToStopWordsFile = "No File Choosen";
        private ObservableCollection<string> _RunSelection = new ObservableCollection<string> { "BOTH", "Clustered","Dynamical"};
        private ObservableCollection<string> _LanguageSelection = new ObservableCollection<string> { "English", "Hebrew" };
        private string _ChoosenRun = "Dynamical";
        private string _ChoosenLanguage = "English";
        private int _StopWordsListChecked,_NgramSize,_SegmentSize;
        private bool _AnalyzeEnabled = true; //TODO
        #endregion

        public void save()
        {
            saveData sd = new saveData();
            sd.NGramSize = NgramSize;
            sd.segSize = SegmentSize;
            sd.TextName = PathToMainInputFile.Substring(PathToMainInputFile.LastIndexOf("/"));
            sd.Language = ChoosenLanguage;
        }


        #region Properties
        /*Properties*/
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
                _SegmentSize = int.Parse(value);
                RaisePropertyChanged("SegmentSize");
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
                _NgramSize = int.Parse(value); RaisePropertyChanged("NgramSize");
            }
        }

        public int StopWordsListChecked
        {
            get { return _StopWordsListChecked; }
            set { _StopWordsListChecked = value; RaisePropertyChanged("StopWordsListChecked"); }
        }
        public string ChoosenRun
        {
            get { return _ChoosenRun; }
            set { _ChoosenRun = value; }
        }

        public string ChoosenLanguage
        {
            get { return _ChoosenLanguage; }
            set { _ChoosenLanguage = value; }
        }

        public ObservableCollection<string> LanguageSelection
        {
            get
            {
                return _LanguageSelection;
            }
        }
        public ObservableCollection<string> RunSelection
        {
            get
            {
                return _RunSelection;
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
}