using PlagiarismUI.InfraS;
using PlagiarismUI.Views;
using System;
using System.Threading;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Text.RegularExpressions;
namespace PlagiarismUI
{
    /// <summary>
    /// Interaction logic for MainShellView.xaml
    /// </summary>
    public partial class MainShellView : Window
    {
        private ICommand _saveCommand;
        public Pipe enginePipe;
        public volatile bool varsSended = false;

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

        
        //Thread connectionThread;

        //private void initForm()
        //{
        //    bool isConnected =enginePipe.connect();
        //    while (isConnected)
        //    {
                
        //        string s = enginePipe.getEngineMessage();
        //        enginePipe.sendEngineMove("Accepted");
        //        if (s == "quit")
        //        {

        //        }
        //        switch (s)
        //        {
        //            case "ERROR":
        //                MessageBoxResult result = MessageBox.Show("An error Occured in CPP Engine, Please look at the Log Files", "Confirmation", MessageBoxButton.OK, MessageBoxImage.Question);
        //                if (result == MessageBoxResult.OK)
        //                {
        //                    Thread.CurrentThread.Abort();
        //                    System.Windows.Application.Current.Shutdown();/*Close app*/
        //                }
        //            break;
        //        }
                
        //    }
        //}

        public MainShellView()
        {

            enginePipe = new Pipe("PlagPipe");
            enginePipe.connect();

                //connectionThread = new Thread(initForm);
            //connectionThread.Start();
         //   connectionThread.IsBackground = true;


            InitializeComponent();
            this.DataContext = new MainShellViewModel();
        }

        private bool ValidateInput()
        {
            return true;
        }


        private bool StartBackgroundWork()
        {
            if (ValidateInput())
            {
                var DC = this.DataContext as MainShellViewModel;

                enginePipe.sendEngineMove("NGRAMSIZE");
                enginePipe.sendEngineMove(DC.NgramSize.ToString());
                enginePipe.sendEngineMove("SEGMENTSIZE");
                enginePipe.sendEngineMove(DC.SegmentSize.ToString());
                enginePipe.sendEngineMove("EXAMINESTOPWORDFILE");
                enginePipe.sendEngineMove(DC.PathToMainInputFile);
                enginePipe.sendEngineMove("EXAMINEPATHFILE");
                enginePipe.sendEngineMove(DC.PathToStopWordsFile);
                enginePipe.sendEngineMove("STARTWORK");
               
                return true;
            }
            else
                return false;
            
        }

        private void AnalyzeTextButton(object sender, RoutedEventArgs e)
        {
            
            if (true == StartBackgroundWork())
            {
                enginePipe.close();
                LoadingWindow LW = new LoadingWindow(this);
                var Location = this.PointToScreen(new Point(0, 0));
                LW.Left = Location.X;
                LW.Top = Location.Y;
                this.Hide();
                LW.ShowDialog();
                
               
                enginePipe = new Pipe("PlagPipe");
                enginePipe.connect();
            }
            else
            {
                //pop up error message
                MessageBox.Show("Please Fill all fields", "Invalid input", MessageBoxButton.OK);
            }
           
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


        
    private void NumberValidationTextBox(object sender, TextCompositionEventArgs e)
    {
        Regex regex = new Regex("[^0-9]+");
        e.Handled = regex.IsMatch(e.Text);
    }

    private void OnWindowClosing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            enginePipe.sendEngineMove("QUIT");
            enginePipe.getEngineMessage();
        }
    }
}

