using System;
using System.Drawing;
using System.Runtime.InteropServices;

namespace AviLib
{
    class Avi
    {
        protected int aviFile;
        protected IntPtr aviStream;

        private int frameSize;
        public int FrameSize
        {
            get { return frameSize; }
        }

        protected double frameRate;
        public double FrameRate
        {
            get { return frameRate; }
        }

        private int width;
        public int Width
        {
            get { return width; }
        }

        private int height;
        public int Height
        {
            get { return height; }
        }

        private Int16 countBitsPerPixel;
        public Int16 CountBitsPerPixel
        {
            get { return countBitsPerPixel; }
        }

        private void SetFormat(IntPtr aviStream)
        {
            AviWrapper.BITMAPINFOHEADER bi = new AviWrapper.BITMAPINFOHEADER();
            bi.biSize = Marshal.SizeOf(bi);
            bi.biWidth = width;
            bi.biHeight = height;
            bi.biPlanes = 1;
            bi.biBitCount = countBitsPerPixel;
            bi.biSizeImage = frameSize;

            int result = AviWrapper.AVIStreamSetFormat(aviStream, 0, ref bi, bi.biSize);
            if (result != 0) { throw new Exception("Error in VideoStreamSetFormat: " + result.ToString()); }
        }

        private void CreateStreamWithoutFormat()
        {
            int scale = 1;
            double rate = frameRate;
            //now we don't use scale
            //GetRateAndScale(ref rate, ref scale);

            AviWrapper.AVISTREAMINFO strhdr = new AviWrapper.AVISTREAMINFO();
            strhdr.fccType = AviWrapper.mmioStringToFOURCC("vids", 0);
            strhdr.fccHandler = AviWrapper.mmioStringToFOURCC("CVID", 0);
            strhdr.dwFlags = 0;
            strhdr.dwCaps = 0;
            strhdr.wPriority = 0;
            strhdr.wLanguage = 0;
            strhdr.dwScale = (int)scale;
            strhdr.dwRate = (int)rate; // Frames per Second
            strhdr.dwStart = 0;
            strhdr.dwLength = 0;
            strhdr.dwInitialFrames = 0;
            strhdr.dwSuggestedBufferSize = frameSize; //height_ * stride_;
            strhdr.dwQuality = -1;        //default
            strhdr.dwSampleSize = 0;
            strhdr.rcFrame.top = 0;
            strhdr.rcFrame.left = 0;
            strhdr.rcFrame.bottom = (uint)height;
            strhdr.rcFrame.right = (uint)width;
            strhdr.dwEditCount = 0;
            strhdr.dwFormatChangeCount = 0;
            strhdr.szName = new UInt16[64];

            int result = AviWrapper.AVIFileCreateStream(aviFile, out aviStream, ref strhdr);

            if (result != 0)
            {
                throw new Exception("Exception in AVIFileCreateStream: " + result.ToString());
            }
        }
    }
}
