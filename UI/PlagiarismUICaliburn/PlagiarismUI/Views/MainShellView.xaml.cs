using PlagiarismUI.InfraS;
using PlagiarismUI.Views;
using System;
using System.Threading;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace PlagiarismUI
{
    /// <summary>
    /// Interaction logic for MainShellView.xaml
    /// </summary>
    public partial class MainShellView : Window
    {
        private ICommand _saveCommand;

        public ICommand SaveCommand
        {
            get
            {
                if (_saveCommand == null)
                {
                    _saveCommand = new RelayCommand(
                        param => this.SaveObject(),
                        param => this.CanSave()
                    );
                }
                return _saveCommand;
            }
        }

        
        

        private bool CanSave()
        {
            // Verify command can be executed here
            return true;
        }

        private void SaveObject()
        {
            // Save command execution logic
        }

        private Pipe enginePipe;
        Thread connectionThread;

        private void initForm()
        {
            while (true)
            {
                enginePipe.connect();
                string s = enginePipe.getEngineMessage();
                enginePipe.sendEngineMove("Accepted");
                if (s == "quit")
                {

                }
                switch (s)
                {
                    case "ERROR":
                        MessageBoxResult result = MessageBox.Show("An error Occured in CPP Engine, Please look at the Log Files", "Confirmation", MessageBoxButton.OK, MessageBoxImage.Question);
                        if (result == MessageBoxResult.OK)
                        {
                            Thread.CurrentThread.Abort();
                            System.Windows.Application.Current.Shutdown();/*Close app*/
                        }
                    break;
                }
                
            }
        }

        public MainShellView()
        {

            enginePipe = new Pipe();
            connectionThread = new Thread(initForm);
            connectionThread.Start();
            connectionThread.IsBackground = true;


            InitializeComponent();
            this.DataContext = new MainShellViewModel();
        }




        private void AnalyzeTextButton(object sender, RoutedEventArgs e)
        {
            
            LoadingWindow LW = new LoadingWindow(this);
            var Location = this.PointToScreen(new Point(0, 0));
            LW.Left = Location.X;
            LW.Top = Location.Y;
            this.Hide();
            LW.ShowDialog();
            
        }
        
        private void BrowseFileClicked(object sender, RoutedEventArgs e)
        {
            // Create OpenFileDialog 
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();



            // Set filter for file extension and default file extension 
            dlg.DefaultExt = ".txt";
            dlg.Filter = "Text Files (*.txt)|*.txt|All Files (*.*)|*.*";


            // Display OpenFileDialog by calling ShowDialog method 
            Nullable<bool> result = dlg.ShowDialog();


            // Get the selected file name and display in a TextBox 
            if (result == true)
            {
                // Open document 
                string filename = dlg.FileName;
                var DC = this.DataContext as MainShellViewModel;
                if ((sender as Button).Name == "FileBrowseStopWordsButton")
                    DC.PathToStopWordsFile = filename;
                else
                    DC.PathToMainInputFile = filename;
               
            }
        }
    }
}

