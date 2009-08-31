using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Configuration;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Text.RegularExpressions;
using System.Diagnostics;
using System.Threading;
//using SharpFFmpeg;
using System.IO;

namespace CSharp_Client
{
    public partial class AppForm : Form
    {
        /*[DllImport("Mpeg2Dec.dll")]
        public static extern mpeg2dec_t mpeg2_init();*/

        private bool started;

        public AppForm()
        {
            started = false;
            InitializeComponent();

            FileTextBox.Enabled = false;
            FileRadioButton.Checked = false;

            StreamTextBox.Enabled = true;
            StreamRadioButton.Checked = true;
        }

        private void AppForm_Load(object sender, EventArgs e)
        {
        }

        private void StartButton_Click(object sender, EventArgs e)
        {
            started = true;
            int fps = 0;
            try
            {
                fps = int.Parse(FPSTextBox.Text.ToString());
            }
            catch (Exception ex)
            {
                FPSTextBox.Text = ex.ToString();
            }

            if (StreamRadioButton.Checked)
            {
                FileTextBox.Text = StreamTextBox.Text.ToString();
                FFMpeg.parceVideoFromStream(StreamTextBox.Text, "video", 240, 320, 6);
            }

            if (FileRadioButton.Checked)
            {
                StreamTextBox.Text = FileTextBox.Text.ToString();
                FFMpeg.parceVideoFromFile(FileTextBox.Text.ToString(), "video", 240, 320, fps);
            }
        }

        private void StopButton_Click(object sender, EventArgs e)
        {
            started = false;
        }

        private void StreamRadioButton_CheckedChanged(object sender, EventArgs e)
        {
            FileTextBox.Enabled = false;
            StreamTextBox.Enabled = true;
        }

        private void FileRadioButton_CheckedChanged(object sender, EventArgs e)
        {
            FileTextBox.Enabled = true;
            StreamTextBox.Enabled = false;
        }
    }

    class FFMpeg
    {

        public string Width
        {
            get { return _width; }
            set { }
        }

        public string Height
        {
            get { return _height; }
            set { }
        }

        public string Fps
        {
            get { return _fps; }
            set { }
        }

        public string Duration
        {
            get { return _duration; }
            set { }
        }

        public string FileName
        {
            get { return _filename; }
            set { _filename = value; }
        }

        public bool IsVideo
        {
            get { return _foundInput0; }
            set { }
        }

        private static string _width;
        private static string _height;
        private static string _fps;
        private static string _duration;
        private static string _filename;
        private static bool _foundInput0 = false;

        public FFMpeg()
        {
            _filename = @"d:\ffmpeg\arts10.flv";
        }

        public FFMpeg(string File)
        {
            _filename = File;
        }

        //ffmpeg -f mjpeg -i http://192.168.0.9/mjpg/video.mjpg video.mjpg
        public static void parceVideoFromStream(string streamName, string targetFileName, int height, int width, int fps)
        {
            System.Diagnostics.Process p = new System.Diagnostics.Process();
            p.EnableRaisingEvents = false;
            p.StartInfo.FileName = @"ffmpeg.exe";
            p.StartInfo.Arguments = " -f mjpeg -i " + streamName + targetFileName + ".mjpg";
            p.StartInfo.CreateNoWindow = false;
            p.StartInfo.UseShellExecute = false;
            p.StartInfo.RedirectStandardOutput = true;
            p.StartInfo.RedirectStandardError = true;
            p.StartInfo.RedirectStandardInput = false;
            p.Start();
            p.BeginErrorReadLine();
            p.WaitForExit();
            p.Close();
        }

        //ffmpeg -i video.flv -an -r 1 -y -s 320×240 video%d.jpg
        public static void parceVideoFromFile(string fileName, string targetFileName, int height,int width, int fps)
        {
            System.Diagnostics.Process p = new System.Diagnostics.Process();
            p.EnableRaisingEvents = false;
            p.StartInfo.FileName = @"ffmpeg.exe";
            string arg = "";
            if (fps != 0)
            {
                arg = " -r " + fps.ToString();
            }
            p.StartInfo.Arguments = " -i " + fileName + arg + " -an -r 1 -y " + targetFileName + "%d.jpg" ;
            //ffmpeg -i nodame_theme.flv -ab 128 -ar 44100 nodame_theme.mp3
            //Grab the audio stream: -i is to specified input file, -ab audio bitrate, -ar audio sampling frequency
            //ffmpeg -i http://64.236.34.97:80/stream/1005 -ab 128 -ar 44100 smoothjazz.mp3
            //Parameters are written in Arguments Field..
            p.StartInfo.CreateNoWindow = false;
            p.StartInfo.UseShellExecute = false;
            p.StartInfo.RedirectStandardOutput = true;
            p.StartInfo.RedirectStandardError = true;
            p.StartInfo.RedirectStandardInput = false;
            p.Start();
            p.BeginErrorReadLine();
            p.WaitForExit();
            p.Close();
        }

        public void CheckVideo()
        {

            System.Diagnostics.Process p = new System.Diagnostics.Process();
            p.EnableRaisingEvents = false;
            p.StartInfo.FileName = @"ffmpeg.exe";
            p.StartInfo.Arguments = "-i " + _filename;
            p.StartInfo.CreateNoWindow = false;
            p.StartInfo.UseShellExecute = false;
            p.StartInfo.RedirectStandardOutput = true;
            p.StartInfo.RedirectStandardError = true;
            p.StartInfo.RedirectStandardInput = false;

            p.ErrorDataReceived += new DataReceivedEventHandler(checkVideoHandler);

            p.Start();
            p.BeginErrorReadLine();
            p.WaitForExit();
            p.Close();

        }

        private static void checkVideoHandler(object sender, DataReceivedEventArgs outLine)
        {
            if (!String.IsNullOrEmpty(outLine.Data))
            {
                string tmp = outLine.Data.Trim();

                // looks ok, probably a video
                if (Regex.IsMatch(tmp, "^Input #0")) _foundInput0 = true;

                // get the duration
                Match m = Regex.Match(tmp, @"^Duration: (\d+:\d+:\d+\.\d+),");
                if (_foundInput0 && m.Success) _duration = m.Groups[1].Captures[0].ToString();

                // get width, height, fps and pixelformat
                if (_foundInput0 && Regex.IsMatch(tmp, @"^Stream #0\.0(\(eng\))?: Video: "))
                {
                    _width = tmp.Split(',')[2].Trim().Split(' ')[0].Split('x')[0];
                    _height = tmp.Split(',')[2].Trim().Split(' ')[0].Split('x')[1];
                    _fps = tmp.Split(',')[3].Trim().Split(' ')[0];
                }
            }
        }
    }
}
