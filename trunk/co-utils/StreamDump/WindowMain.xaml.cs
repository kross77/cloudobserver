using Microsoft.Win32;
using System;
using System.IO;
using System.Net;
using System.Threading;
using System.Windows;

namespace StreamDump
{
    public partial class WindowMain : Window
    {
        private bool dumping;
        private bool Dumping
        {
            get { return dumping; }
            set
            {
                dumping = value;
                textBoxStreamUri.IsReadOnly = dumping;
                textBoxDumpFile.IsReadOnly = dumping;
                buttonDumpFileBrowse.IsEnabled = !dumping;
                if (dumping)
                {
                    buttonStartStopDump.Content = "Stop Dump";
                    textBlockStatus.Text = "Dumping: ";
                }
                else
                {
                    buttonStartStopDump.Content = "Start Dump";
                    textBlockStatus.Text = "Ready to dump.";
                }
            }
        }
        private Thread dumpThread;

        private long bytesDumped;
        private long BytesDumped
        {
            get { return bytesDumped; }
            set
            {
                bytesDumped = value;
                Dispatcher.Invoke(new ThreadStart(delegate { textBlockStatus.Text = "Dumping: " + value.ToString() + " bytes dumped."; }));
            }
        }

        private Stream sourceStream;
        private FileStream destinationStream;

        private const int bufferSize = 8192;

        public WindowMain()
        {
            InitializeComponent();
        }

        private void buttonDumpFileBrowse_Click(object sender, RoutedEventArgs e)
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.Filter = "All Files (*.*)|*.*";
            saveFileDialog.FileName = textBoxDumpFile.Text;
            if (saveFileDialog.ShowDialog() == true)
                textBoxDumpFile.Text = saveFileDialog.FileName;
        }

        private void buttonStartStopDump_Click(object sender, RoutedEventArgs e)
        {
            if (!Dumping)
            {
                if (File.Exists(textBoxDumpFile.Text))
                    if (MessageBox.Show("Dump file already exists. Rewrite?", "Attention", MessageBoxButton.YesNo, MessageBoxImage.Question) == MessageBoxResult.No)
                        return;

                try
                {
                    sourceStream = WebRequest.Create(textBoxStreamUri.Text).GetResponse().GetResponseStream();
                }
                catch (Exception exception)
                {
                    MessageBox.Show("Cannot connect to the stream. Details: " + exception.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                    return;
                }

                try
                {
                    destinationStream = File.Create(textBoxDumpFile.Text);
                }
                catch (Exception exception)
                {
                    MessageBox.Show("Cannot create the dump file. Details: " + exception.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                    return;
                }

                Dumping = true;
                bytesDumped = 0;
                dumpThread = new Thread(DumpLoop);
                dumpThread.IsBackground = true;
                dumpThread.Start();
            }
            else
            {
                Dumping = false;

                try
                {
                    sourceStream.Close();
                    destinationStream.Close();
                }
                catch (Exception)
                {
                }
            }
        }

        private void DumpLoop()
        {
            int read = 0;
            byte[] buffer = new byte[bufferSize];

            while (dumping)
            {
                try
                {
                    read = sourceStream.Read(buffer, 0, bufferSize);
                    destinationStream.Write(buffer, 0, read);
                    BytesDumped += read;
                }
                catch (Exception)
                {
                    Dispatcher.Invoke(new ThreadStart(delegate { Dumping = false; }));
                }
            }
        }
    }
}
