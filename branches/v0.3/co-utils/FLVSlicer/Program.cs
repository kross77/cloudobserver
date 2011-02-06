using System;
using System.IO;
using System.Windows.Forms;

namespace CloudObserver.Utils.FLVSlicer
{
    public static class Program
    {
        [STAThread]
        public static void Main(string[] args)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "FLV Files (*.flv)|*.flv|All Files (*.*)|*.*";
            if (openFileDialog.ShowDialog() != DialogResult.OK)
                return;

            Console.Write("Start timestamp: ");
            uint startTimestamp = UInt32.Parse(Console.ReadLine());

            Console.Write("End timestamp: ");
            uint endTimestamp = UInt32.Parse(Console.ReadLine());

            FileStream input = File.OpenRead(openFileDialog.FileName);
            FLVSlicer flvSlicer = new FLVSlicer(input);

            FileStream audioOutput = File.Create("audio.flv");
            flvSlicer.GetAudio(audioOutput);
            audioOutput.Close();

            FileStream videoOutput = File.Create("video.flv");
            flvSlicer.GetVideo(videoOutput);
            videoOutput.Close();

            FileStream sliceOutput = File.Create("slice.flv");
            Console.WriteLine("Slice duration: " + flvSlicer.GetSlice(sliceOutput, startTimestamp, endTimestamp).ToString());
            sliceOutput.Close();

            input.Close();

            Console.Write("Press any key to exit...");
            Console.ReadKey();
        }
    }
}
