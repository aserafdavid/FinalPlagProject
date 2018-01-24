using Microsoft.Windows.Controls.Primitives;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Controls.DataVisualization.Charting;
using System.Windows.Media;

namespace PlagiarismUI.ViewModels
{
    class ResultwindowViewModel : UserControl, INotifyPropertyChanged
    {

       private string _TextName;
       private string _SegSize;
       private string _NGramSize;
       private string _Clusters;
       private string _Lang;
        public string TextName
        {
            get { return _TextName; }
            set { _TextName = value; }
        }
        public string SegSize
        {
            get { return _SegSize; }
            set { _SegSize = value; }
        }
        public string NGramSize
        {
            get { return _NGramSize; }
            set { _NGramSize = value; }
        }
        public string Clusters
        {
            get { return _Clusters; }
            set { _Clusters = value; }
        }
        public string Lang
        {
            get { return _Lang; }
            set { _Lang = value; }
        }
        private void setAlgorithmInput()
        {

        }
        public ResultwindowViewModel()
        {
            setAlgorithmInput();
        }

        public ObservableCollection<Data> Items { get; } = new ObservableCollection<Data>();

        private void Populate()
        {
            Items.Add(new Data() { background = Brushes.Blue }); 
             Items.Add(new Data() { background = Brushes.Blue }); 
           Items.Add(new Data() { background = Brushes.Blue }); 
           Items.Add(new Data() { background = Brushes.Red }); 
           Items.Add(new Data() { background = Brushes.Blue }); 
           Items.Add(new Data() { background = Brushes.Red });
            Items.Add(new Data() { background = Brushes.Blue });
        }


        public void SetGraph()
        {

        }



        private Brush _GridBackGround;
       public Brush GridBackGround
        {
            get { return _GridBackGround; }
            set { _GridBackGround = value; }
        }


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
    public class Data
    {

        public Brush background { get; set;}
    }

}
