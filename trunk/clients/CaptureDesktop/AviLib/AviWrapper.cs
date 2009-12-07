using System;
using System.Drawing;
using System.Runtime.InteropServices;

namespace AviLib
{
    public class AviWrapper
    {
        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct RECT
        {
            public UInt32 left;
            public UInt32 top;
            public UInt32 right;
            public UInt32 bottom;
        }
        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct AVISTREAMINFO
        {
            public Int32 fccType;
            public Int32 fccHandler;
            public Int32 dwFlags;
            public Int32 dwCaps;
            public Int16 wPriority;
            public Int16 wLanguage;
            public Int32 dwScale;
            public Int32 dwRate;
            public Int32 dwStart;
            public Int32 dwLength;
            public Int32 dwInitialFrames;
            public Int32 dwSuggestedBufferSize;
            public Int32 dwQuality;
            public Int32 dwSampleSize;
            public RECT rcFrame;
            public Int32 dwEditCount;
            public Int32 dwFormatChangeCount;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
            public UInt16[] szName;
        }
        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct BITMAPINFOHEADER
        {
            public Int32 biSize;
            public Int32 biWidth;
            public Int32 biHeight;
            public Int16 biPlanes;
            public Int16 biBitCount;
            public Int32 biCompression;
            public Int32 biSizeImage;
            public Int32 biXPelsPerMeter;
            public Int32 biYPelsPerMeter;
            public Int32 biClrUsed;
            public Int32 biClrImportant;
        }
        //hren kakay to
        [DllImport("winmm.dll", EntryPoint = "mmioStringToFOURCCA")]
        public static extern int mmioStringToFOURCC(String sz, int uFlags);

        //Open an AVI file
        [DllImport("avifil32.dll", PreserveSig = true)]
        public static extern int AVIFileOpen(
            ref int ppfile,
            String szFile,
            int uMode,
            int pclsidHandler);

        //Set the format for a new stream
        [DllImport("avifil32.dll")]
        public static extern int AVIStreamSetFormat(
            IntPtr aviStream, Int32 lPos,
            ref BITMAPINFOHEADER lpFormat, Int32 cbFormat);

        //Create a new stream in an open AVI file
        [DllImport("avifil32.dll")]
        public static extern int AVIFileCreateStream(
            int pfile,
            out IntPtr ppavi,
            ref AVISTREAMINFO ptr_streaminfo);

    }
}
