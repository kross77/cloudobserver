using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Drawing.Imaging;
using System.Drawing;
using System.Windows.Forms;

namespace CaptureDesktop
{
    class CaptureDesktop
    {
        private static TimerCallback timerDelegate = new TimerCallback(CaptureDesktop.CaptureFrame);
        private static System.Threading.Timer timer = null;


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
        /// <summary>
        /// internal function/ it's called by timer for capture one desktop frame
        /// </summary>
        /// <param name="stateInfo"></param>
        private static void CaptureFrame(Object stateInfo)
        {            
            Bitmap Bitmap;
            Graphics Graps;

            Bitmap = new Bitmap(Screen.PrimaryScreen.Bounds.Width, Screen.PrimaryScreen.Bounds.Height, PixelFormat.Format32bppArgb);
            Graps = Graphics.FromImage(Bitmap);
            Graps.CopyFromScreen(Screen.PrimaryScreen.Bounds.X, Screen.PrimaryScreen.Bounds.Y, 0, 0, Screen.PrimaryScreen.Bounds.Size, CopyPixelOperation.SourceCopy);
            //Bitmap.Save(System.Environment.GetFolderPath(Environment.SpecialFolder.Desktop) + "\\YourShot.jpeg", ImageFormat.Jpeg);
            Bitmap.Save("YourShot" + DateTime.Now.ToString("h_mm_ss_fff") + ".jpeg", ImageFormat.Jpeg);
        }

        public int Start(int freq)
        {
            //if we already started capture return error
            if (1 == State)
            {
                return -1;
            }
            timer = new System.Threading.Timer(timerDelegate, null, 0, freq);
            return 0;
        }

        public void Stop()
        {            
            timer.Dispose();
            timer = null;
        }
    }
}
