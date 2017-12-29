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
        Pipe pipe;
        public LoadingWindow(Window window, Pipe enginePipe)
        {
            pipe = enginePipe;
            InitializeComponent();
            _previousWindow = window;
        }

        private void backFromLoading_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
            _previousWindow.Show();
     
            pipe.sendEngineMove("CANCELRUN");
            string s=pipe.getEngineMessage();
        }
    }
}
