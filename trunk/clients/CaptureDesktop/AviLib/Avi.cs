using System;
using System.Drawing;
using System.Runtime.InteropServices;

namespace AviLib
{
    public class Avi
    {
        private static int countFiles;

        public static AviFile CreateFile(string fileName)
        {
            if (countFiles == 0)
            {
                countFiles++;
                AviWrapper.AVIFileInit();
            }

            return AviFile.CreateFile(fileName);
        }

        public static VideoStream AddVideoStream(AviFile aviFile, FrameParams frameParams, int frameRate)
        {
            return VideoStream.CreateVideoStream(aviFile.FileID, frameParams, frameRate);
        }

        //public static AudioStream AddAudioStream(AviFile fileID)
        //{
        //    return null;
        //}

        public static int CloseFile(AviFile aviFile)
        {
            aviFile.CloseFile();
           
            if (0 == countFiles-- )
            {
                countFiles++;
                AviWrapper.AVIFileExit();
            }

            return countFiles;
        }
    }
}
