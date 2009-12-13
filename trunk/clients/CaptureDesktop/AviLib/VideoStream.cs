using System;
using System.IO;
using System.Drawing;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;

namespace AviLib
{
    public struct FrameParams
    {
        public int frameSize;
        public int width;
        public int height;
        public Int16 countBitsPerPixel;
    }
    public class VideoStream
    {
        //protected int aviFile;
        protected IntPtr aviStream;

        protected double frameRate;
        public double FrameRate
        {
            get { return frameRate; }
        }
        private int frameScale;

        public int FrameScale
        {
            get { return frameScale; }
        }

        FrameParams frameParams;

        internal FrameParams FrameParams
        {
            get { return frameParams; }
        }

        private int countFrames;

        private VideoStream(IntPtr aviStream, FrameParams frameParams, int frameRate, int frameScale)
        {
            this.aviStream = aviStream;
            this.frameRate = frameRate;
            this.frameScale = frameScale;
            this.frameParams = frameParams;
            this.countFrames = 0;
        }
        private static void SetFormat(IntPtr aviStream, FrameParams frameParams)
        {
            AviWrapper.BITMAPINFOHEADER bi = new AviWrapper.BITMAPINFOHEADER();
            bi.biSize = Marshal.SizeOf(bi);
            bi.biWidth = frameParams.width;
            bi.biHeight = frameParams.height;
            bi.biPlanes = 1;
            bi.biBitCount = frameParams.countBitsPerPixel;
            bi.biSizeImage = frameParams.frameSize;

            int result = AviWrapper.AVIStreamSetFormat(aviStream, 0, ref bi, bi.biSize);
            if (result != 0) { throw new Exception("Error in VideoStreamSetFormat: " + result.ToString()); }
        }

        private static IntPtr CreateStreamWithoutFormat(int fileID, FrameParams frameParams, int frameRate, int frameScale)
        {
            AviWrapper.AVISTREAMINFO strhdr = new AviWrapper.AVISTREAMINFO();
            strhdr.fccType = AviWrapper.mmioStringToFOURCC("vids", 0);
            strhdr.fccHandler = AviWrapper.mmioStringToFOURCC("CVID", 0);
            strhdr.dwFlags = 0;
            strhdr.dwCaps = 0;
            strhdr.wPriority = 0;
            strhdr.wLanguage = 0;
            strhdr.dwScale = (int)frameScale;
            strhdr.dwRate = (int)frameRate;
            strhdr.dwStart = 0;
            strhdr.dwLength = 0;
            strhdr.dwInitialFrames = 0;
            strhdr.dwSuggestedBufferSize = frameParams.frameSize;
            strhdr.dwQuality = -1;        //default
            strhdr.dwSampleSize = 0;
            strhdr.rcFrame.top = 0;
            strhdr.rcFrame.left = 0;
            strhdr.rcFrame.bottom = (uint)frameParams.height;
            strhdr.rcFrame.right = (uint)frameParams.width;
            strhdr.dwEditCount = 0;
            strhdr.dwFormatChangeCount = 0;
            strhdr.szName = new UInt16[64];

            IntPtr aviStream = (IntPtr)0;
            int result = AviWrapper.AVIFileCreateStream(fileID, out aviStream, ref strhdr);

            if (result != 0)
            {
                throw new Exception("Exception in AVIFileCreateStream: " + result.ToString());
            }
            return aviStream;
        }

        public static VideoStream CreateVideoStream(int fileID, FrameParams frameParams, int frameRate)
        {
            try
            {
                IntPtr aviStream = CreateStreamWithoutFormat(fileID, frameParams, frameRate, 1);
                SetFormat(aviStream, frameParams);                
                return new VideoStream(aviStream, frameParams, frameRate, 1);
            }
            catch (Exception)
            {
                return null;
            }
        }

        private static Int16 ConvertPixelFormatToBitCount(PixelFormat format)
        {
            String formatName = format.ToString();
            if (formatName.Substring(0, 6) != "Format")
            {
                throw new Exception("Unknown pixel format: " + formatName);
            }

            formatName = formatName.Substring(6, 2);
            Int16 bitCount = 0;
            if (Char.IsNumber(formatName[1]))
            {	//16, 32, 48
                bitCount = Int16.Parse(formatName);
            }
            else
            {	//4, 8
                bitCount = Int16.Parse(formatName[0].ToString());
            }

            return bitCount;
        }
        public static FrameParams BmpToFrameParams(Bitmap bmp)
        {
            FrameParams parFrame = new FrameParams();
            BitmapData bmpData = bmp.LockBits(
                new Rectangle(0, 0, bmp.Width, bmp.Height),
                ImageLockMode.ReadOnly, bmp.PixelFormat);

            parFrame.frameSize = bmpData.Stride * bmpData.Height;
            parFrame.width = bmp.Width;
            parFrame.height = bmp.Height;
            parFrame.countBitsPerPixel = ConvertPixelFormatToBitCount(bmpData.PixelFormat);

            bmp.UnlockBits(bmpData);
            return parFrame;
        }
        public int AddFrame(Bitmap bmp)
        {
            bmp.RotateFlip(RotateFlipType.RotateNoneFlipY);

            BitmapData bmpDat = bmp.LockBits(
                new Rectangle(
                0, 0, bmp.Width, bmp.Height),
                ImageLockMode.ReadOnly, bmp.PixelFormat);

            int result = AviWrapper.AVIStreamWrite(
                aviStream, //stream ptr
                countFrames, //number of frame in stream
                1, // quantity of frames for writting
                bmpDat.Scan0, //pointer to data
                (Int32)(bmpDat.Stride * bmpDat.Height), //size of frame
                0, 0, 0);

            bmp.UnlockBits(bmpDat);

            if (result != 0)
            {
                throw new Exception("Exception in VideoStreamWrite: " + result.ToString());
            }

            return countFrames++;
        }
        public void Close()
        {
            AviWrapper.AVIStreamRelease(aviStream);
        }
    }
}
