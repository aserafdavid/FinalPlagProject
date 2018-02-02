using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PlagiarismUI.InfraS
{
    public static class ConnectionManager
    {
        private static Pipe enginePipe;
        private static Pipe UIenginePipe;
        private static Pipe PlagPipe;

        private static bool is_enginePipeConnected = false;
        private static bool is_UIenginePipeConnected = false;
        private static bool is_PlagPipeEnginePipeConnected = false;

        public static Pipe GetPlagPipe()
        {
            if (!is_PlagPipeEnginePipeConnected)
            {
                ConnectPlagEnginePipe();
            }
            return enginePipe;
        }

        public static void ConnectPlagEnginePipe()
        {
            PlagPipe = new Pipe("PlagPipe"); //PIPELOADNAME
            PlagPipe.connect();
            is_PlagPipeEnginePipeConnected = true;
        }

        public static Pipe GetEnginePipe()
        {
            if (!is_enginePipeConnected)
            {
                ConnectEnginePipe();
                is_enginePipeConnected = true;
            }
            return enginePipe;
        }

        public static Pipe GetUIenginePipe()
        {
            if (!is_UIenginePipeConnected)
            {
                ConnectUIenginePipe();
            }
            return UIenginePipe;
        }



        public static void ConnectEnginePipe()
        {
            enginePipe = new Pipe("PIPELOADNAME"); //PIPELOADNAME
            enginePipe.connect();
            is_enginePipeConnected = true;

        }
        public static string GetengineMessage()
        {
            return enginePipe.getEngineMessage();
        }

        public static string GetUIengineMessage()
        {
            return UIenginePipe.getEngineMessage();
        }


        public static void CloseUIengine()
        {
            UIenginePipe.close();
            is_UIenginePipeConnected = false;
        }
        public static void ClosePlagPipeEngine()
        {
            PlagPipe.close();
            is_PlagPipeEnginePipeConnected = false;
        }
        public static void CloseEnginePipe()
        {
            enginePipe.close();
            is_enginePipeConnected = false;
        }
        public static void ConnectUIenginePipe()
        {
            UIenginePipe = new Pipe("PIPEUPDATEUI");
            UIenginePipe.connect();
            is_UIenginePipeConnected = true;
        }

        public static string NgramSize = "";
        public static string fileName = "";
        public static string segSize = "";
        public static string AlgToRun = "";

    public static void saveData(string NGSIZE, string textName, string SegSize,string ChoosenRun)
        {
            int temp = textName.LastIndexOf("\\");
             NgramSize = NGSIZE;
            segSize = SegSize;
            AlgToRun = ChoosenRun;
            fileName = textName.Substring(temp+1);
        }
    }
    


}
