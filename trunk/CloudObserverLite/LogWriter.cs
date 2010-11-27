using System;
using System.IO;

namespace CloudObserverLite
{
    public class LogWriter
    {
        private static LogWriter instance = null;

        //private StreamWriter writer;

        private LogWriter()
        {
            //this.writer = new StreamWriter(File.Create(DateTime.Now.ToString().Replace(':','.') + ".log"));
        }

        public static LogWriter GetInstance()
        {
            if (instance == null)
                instance = new LogWriter();

            return instance;
        }

        public void WriteLog(string message)
        {
            message = DateTime.Now.ToString() + ": " + message;

            //this.writer.WriteLine(message);
            Console.WriteLine(message);
        }

        public void Close()
        {
            //this.writer.Close();
        }
    }
}
