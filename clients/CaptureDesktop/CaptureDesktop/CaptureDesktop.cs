using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Drawing.Imaging;
using System.Drawing;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace CaptureDesktop
{
    class CaptureDesktop
    {
        private static TimerCallback timerDelegate = new TimerCallback(CaptureDesktop.CaptureAndSaveDesktop);
        private static System.Threading.Timer timer = null;
        private static AviLib.AviFile aviFile;
        private static AviLib.VideoStream aviStream;


        protected CaptureDesktop()
        {
        }
        private sealed class CaptureDesktopCreator
        {
            private static readonly CaptureDesktop instance = new CaptureDesktop();
            public static CaptureDesktop Instance { get { return instance; } }
        }
        public static CaptureDesktop Instance
        {
            get
            {
                return CaptureDesktopCreator.Instance;
            }
        }
        /// <summary>
        /// get object's state
        /// return 1 if object is capturing desktop now
        /// else return 0 
        /// </summary>
        public int State 
        {
            get
            {
                if (null == timer)
                    return 0;
                else
                    return 1;                        
            }
        }
/*
        static Bitmap CaptureFrame()
        {
            SIZE size;
            IntPtr hBitmap;
            IntPtr hDC = Win32Stuff.GetDC(Win32Stuff.GetDesktopWindow());
            IntPtr hMemDC = GDIStuff.CreateCompatibleDC(hDC);

            size.cx = Win32Stuff.GetSystemMetrics
                      (Win32Stuff.SM_CXSCREEN);

            size.cy = Win32Stuff.GetSystemMetrics
                      (Win32Stuff.SM_CYSCREEN);

            hBitmap = GDIStuff.CreateCompatibleBitmap(hDC, size.cx, size.cy);

            if (hBitmap != IntPtr.Zero)
            {
                IntPtr hOld = (IntPtr)GDIStuff.SelectObject
                                       (hMemDC, hBitmap);

                GDIStuff.BitBlt(hMemDC, 0, 0, size.cx, size.cy, hDC,
                                               0, 0, GDIStuff.SRCCOPY);

                GDIStuff.SelectObject(hMemDC, hOld);
                GDIStuff.DeleteDC(hMemDC);
                Win32Stuff.ReleaseDC(Win32Stuff.GetDesktopWindow(), hDC);
                Bitmap bmp = System.Drawing.Image.FromHbitmap(hBitmap);
                GDIStuff.DeleteObject(hBitmap);
                GC.Collect();
                return bmp;
            }
            return null;

        }

        public static Bitmap CaptureDesktopWithCursor()
        {
            int cursorX = 0;
            int cursorY = 0;
            Bitmap desktopBMP;
            Bitmap cursorBMP;
            Bitmap finalBMP;
            Graphics g;
            Rectangle r;

            desktopBMP = CaptureFrame();
            cursorBMP = CaptureCursor(ref cursorX, ref cursorY);
            if (desktopBMP != null)
            {
                if (cursorBMP != null)
                {
                    r = new Rectangle(cursorX, cursorY, cursorBMP.Width, cursorBMP.Height);
                    g = Graphics.FromImage(desktopBMP);
                    g.DrawImage(cursorBMP, r);
                    g.Flush();

                    return desktopBMP;
                }
                else
                    return desktopBMP;
            }

            return null;        
        }
        */
       /// <summary>
        /// internal function/ it's called by timer for capture one desktop frame
        /// </summary>
        /// <param name="stateInfo"></param>
        private static Bitmap CaptureFrame()
        {            
            Bitmap bmpDesctop, bmpCursor;
            Graphics g;
            int curX = 0, curY = 0;

            bmpDesctop = new Bitmap(Screen.PrimaryScreen.Bounds.Width, Screen.PrimaryScreen.Bounds.Height, PixelFormat.Format32bppArgb);
            g = Graphics.FromImage(bmpDesctop);
            g.CopyFromScreen(Screen.PrimaryScreen.Bounds.X, Screen.PrimaryScreen.Bounds.Y, 0, 0, Screen.PrimaryScreen.Bounds.Size, CopyPixelOperation.SourceCopy);
            
            bmpCursor = CaptureCursor(ref curX, ref curY);
            Rectangle r = new Rectangle(curX, curY, bmpCursor.Width, bmpCursor.Height);
            g.DrawImage(bmpCursor, r);
            g.Flush();
            return bmpDesctop;
        }
        private static void SaveCaptureFrame(Bitmap bmpFrame)
        {
            try
            {
                aviStream.AddFrame(bmpFrame);
            }
            catch (Exception)
            {
                aviStream.Close();
                AviLib.Avi.CloseFile(aviFile);
            }

            //bmpFrame.Save("YourShot" + DateTime.Now.ToString("h_mm_ss_fff") + ".jpeg", ImageFormat.Jpeg);
        }
        private static void CaptureAndSaveDesktop(Object stateInfo)
        {
            Bitmap bmpDesc = CaptureFrame();
            SaveCaptureFrame(bmpDesc);
        }

        private static Bitmap CaptureCursor(ref int x, ref int y)
        {
            Win32Stuff.CURSORINFO cursorInfo = new Win32Stuff.CURSORINFO();
            cursorInfo.cbSize = Marshal.SizeOf(cursorInfo);
            if (!Win32Stuff.GetCursorInfo(out cursorInfo))
                return null;

            if (cursorInfo.flags != Win32Stuff.CURSOR_SHOWING)
                return null;

            IntPtr hicon = Win32Stuff.CopyIcon(cursorInfo.hCursor);
            if (hicon == IntPtr.Zero)
                return null;

            Win32Stuff.ICONINFO iconInfo;
            if (!Win32Stuff.GetIconInfo(hicon, out iconInfo))
                return null;

            x = cursorInfo.ptScreenPos.x - ((int)iconInfo.xHotspot);
            y = cursorInfo.ptScreenPos.y - ((int)iconInfo.yHotspot);

            using (Bitmap maskBitmap = Bitmap.FromHbitmap(iconInfo.hbmMask))
            {
                // Is this a monochrome cursor?
                if (maskBitmap.Height == maskBitmap.Width * 2)
                {
                    Bitmap resultBitmap = new Bitmap(maskBitmap.Width, maskBitmap.Width);

                    Graphics desktopGraphics = Graphics.FromHwnd(Win32Stuff.GetDesktopWindow());
                    IntPtr desktopHdc = desktopGraphics.GetHdc();

                    IntPtr maskHdc = Win32Stuff.CreateCompatibleDC(desktopHdc);
                    IntPtr oldPtr = Win32Stuff.SelectObject(maskHdc, maskBitmap.GetHbitmap());

                    using (Graphics resultGraphics = Graphics.FromImage(resultBitmap))
                    {
                        IntPtr resultHdc = resultGraphics.GetHdc();

                        // These two operation will result in a black cursor over a white background.
                        // Later in the code, a call to MakeTransparent() will get rid of the white background.
                        Win32Stuff.BitBlt(resultHdc, (IntPtr)0, (IntPtr)0, (IntPtr)32, (IntPtr)32, maskHdc, (IntPtr)0, (IntPtr)32, ((IntPtr)Win32Stuff.TernaryRasterOperations.SRCCOPY));
                        Win32Stuff.BitBlt(resultHdc, (IntPtr)0, (IntPtr)0, (IntPtr)32, (IntPtr)32, maskHdc, (IntPtr)0, (IntPtr)0, (IntPtr)Win32Stuff.TernaryRasterOperations.SRCINVERT);

                        resultGraphics.ReleaseHdc(resultHdc);
                    }

                    IntPtr newPtr = Win32Stuff.SelectObject(maskHdc, oldPtr);
                    Win32Stuff.DeleteDC(newPtr);
                    Win32Stuff.DeleteDC(maskHdc);
                    desktopGraphics.ReleaseHdc(desktopHdc);

                    // Remove the white background from the BitBlt calls,
                    // resulting in a black cursor over a transparent background.
                    resultBitmap.MakeTransparent(Color.White);
                    return resultBitmap;
                }
            }

            Icon icon = Icon.FromHandle(hicon);
            return icon.ToBitmap();
        }


        public int Start(int freq)
        {
            //if we already started capture return error
            if (1 == State)
            {
                return -1;
            }
            //create avi file and stream in it
            aviFile = AviLib.Avi.CreateFile("Capture_" + DateTime.Now.ToString("h_mm_ss_fff") + ".avi");
            Bitmap bmpDesc = CaptureFrame();
            aviStream = AviLib.Avi.AddVideoStream(aviFile, AviLib.VideoStream.BmpToFrameParams(bmpDesc), 1000/freq);
            aviStream.AddFrame(bmpDesc);
           
            timer = new System.Threading.Timer(timerDelegate, null, 0, freq);            
            return 0;
        }

        public void Stop()
        {
            timer.Dispose();
            timer = null;
            aviStream.Close();
            AviLib.Avi.CloseFile(aviFile);
        }
    }
}
