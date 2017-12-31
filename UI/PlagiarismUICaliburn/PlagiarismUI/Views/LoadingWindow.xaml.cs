using PlagiarismUI.InfraS;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace PlagiarismUI.Views
{
    /// <summary>
    /// Interaction logic for LoadingWindow.xaml
    /// </summary>
    public partial class LoadingWindow : Window
    {
        private Window _previousWindow;
        private Pipe enginePipe;
        public LoadingWindow(Window window)
        {
            // pipe = enginePipe;
            enginePipe = new Pipe("PlagPipe");
            enginePipe.connect();
            InitializeComponent();
            _previousWindow = window;
        }

        private void backFromLoading_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
            _previousWindow.Show();

            enginePipe.sendEngineMove("CANCELRUN");
            string s= enginePipe.getEngineMessage();
            if(s =="ACCEPTED")
                 enginePipe.close();
            else
            {
                //TODO add popup window
            }
        }
    }
}
