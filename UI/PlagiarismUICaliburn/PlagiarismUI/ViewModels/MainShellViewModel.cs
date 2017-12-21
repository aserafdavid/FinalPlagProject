using System;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace PlagiarismUI
{
    public class MainShellViewModel : UserControl, INotifyPropertyChanged
    {
        #region properties


        /*fields*/
        private string _PathToMainInputFile = "No File Choosen";
        private string _PathToStopWordsFile = "No File Choosen";
        private ObservableCollection<string> _RunSelection = new ObservableCollection<string> { "BOTH", "Clustered","Dynamical"};

        private string _ChoosenRun = "Dynamical";

        /*Properties*/

        public string ChoosenRun
        {
            get { return _ChoosenRun; }
            set { _ChoosenRun = value; }
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
            set { _PathToStopWordsFile = value; }
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
    
}