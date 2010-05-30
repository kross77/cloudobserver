using System;
using System.Runtime.InteropServices;
using System.Security;
using DirectShowLib;
using System.Windows.Forms;
using CloudObserver.DirectShow.Interfaces;

namespace CloudObserver.DirectShow.Interfaces
{
    [SuppressUnmanagedCodeSecurity]
    [Guid("80AE3F22-17DE-4d6c-BC3E-F2A38AFC53CC")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface ICloudInetControl
    {
        Int32 SetAddress([In, MarshalAs(UnmanagedType.LPWStr)] string pszAddress, int port);
        Int32 GetAddress([Out, MarshalAs(UnmanagedType.LPWStr)] out string hostAddr, out int port);
    }
}

namespace CloudObserver.DirectShow.Filters
{

    //[Guid("37AC047C-BED1-49ef-AB43-BB906A158DD6")]
    public class CloudStreamRenderer
    {
        private static Guid CLSID_CloudStreamRenderer = new Guid("{37AC047C-BED1-49ef-AB43-BB906A158DD6}");
        private static IBaseFilter baseFilter;

        public static IBaseFilter BaseFilter
        {
            get
            {
                if (null == CloudStreamRenderer.baseFilter)
                {
                    CloudStreamRenderer.baseFilter = (IBaseFilter)Activator.CreateInstance(Type.GetTypeFromCLSID(CLSID_CloudStreamRenderer));
                }
                return CloudStreamRenderer.baseFilter;
            }
        }
        public static int SetAddress(string hostAddr, int port)
        {
            ICloudInetControl ctrlInterface = CloudStreamRenderer.BaseFilter as ICloudInetControl;
            if (null == ctrlInterface)
                return -1;

            return ctrlInterface.SetAddress(hostAddr, port);
        }
        public static int GetAddress(out string hostAddr, out int port)
        {
            hostAddr = "                                        ";
            port = 0;
            ICloudInetControl ctrlInterface = CloudStreamRenderer.BaseFilter as ICloudInetControl;
            if (null == ctrlInterface)
                return -1;

            return ctrlInterface.GetAddress(out hostAddr, out port);
        }
    }
    //37AF7C74-9887-42bd-858A-FF4D4035ED47
    public static class CloudFileWriter
    {
        private static Guid CLSID_CloudFileWriter = new Guid("{37AF7C74-9887-42bd-858A-FF4D4035ED47}");
        private static IBaseFilter baseFilter;

        public static IBaseFilter BaseFilter
        {
            get 
            {
                if(null == CloudFileWriter.baseFilter)
                {
                    CloudFileWriter.baseFilter = (IBaseFilter)Activator.CreateInstance(Type.GetTypeFromCLSID(CLSID_CloudFileWriter));                   
                }
                return CloudFileWriter.baseFilter;
            }            
        }
        public static int SetFileName(string fileName)
        {
            IFileSinkFilter fileSink = CloudFileWriter.BaseFilter as IFileSinkFilter;
            if (null == fileSink)
                return -1;

            return fileSink.SetFileName(fileName, null);
        }
    }
}

namespace CloudObserver.DirectShow
{
    public static class Utils
    {
        public static void checkHR(int hr, string message)
        {
            if (hr < 0)
            {
                MessageBox.Show(message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                DsError.ThrowExceptionForHR(hr);
            }
        }
        public static IPin GetPin(IBaseFilter filter, string pinname)
        {
            IEnumPins epins;
            int hr = filter.EnumPins(out epins);
            checkHR(hr, "Can't enumerate pins.");
            IntPtr fetched = Marshal.AllocCoTaskMem(4);
            IPin[] pins = new IPin[1];
            while (epins.Next(1, pins, fetched) == 0)
            {
                PinInfo pinfo;
                pins[0].QueryPinInfo(out pinfo);
                bool found = (pinfo.name == pinname);
                DsUtils.FreePinInfo(pinfo);
                if (found) return pins[0];
            }
            checkHR(-1, "Pin not found.");
            return null;
        }

        public static IPin GetFirstOutputPin(IBaseFilter filter)
        {
            IEnumPins epins;
            int hr = filter.EnumPins(out epins);
            checkHR(hr, "Can't enumerate pins.");
            IntPtr fetched = Marshal.AllocCoTaskMem(4);
            IPin[] pins = new IPin[1];
            while (epins.Next(1, pins, fetched) == 0)
            {
                PinInfo pinfo;
                pins[0].QueryPinInfo(out pinfo);
                bool found = (pinfo.dir == PinDirection.Output);
                DsUtils.FreePinInfo(pinfo);
                if (found) return pins[0];
            }
            checkHR(-1, "Pin not found.");
            return null;
        }
    }
}


