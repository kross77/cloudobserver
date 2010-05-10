using System;
using System.Windows.Forms;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.Runtime.InteropServices.ComTypes;
using DirectShowLib;

using CloudObserver.DirectShow;

using CloudObserver.DirectShow.Filters;

namespace CloudObserver.DirectShow.Graphs
{
    class FileWriterGraphBuilder
    {
        private IGraphBuilder graph;
        private IMediaControl mediaControl;
        
        private Guid CLSID_LAMEAudioEncoder = new Guid("{B8D27088-FF5F-4B7C-98DC-0E91A1696286}"); // lame.ax
        //private Guid CLSID_CloudStreamRenderer = new Guid("{37AC047C-BED1-49ef-AB43-BB906A158DD6}");

        public FileWriterGraphBuilder()
        {
        }
        public int CreateFilter(DsDevice audioInputDevice, string fileName)
        {
            if (null != graph)
                return 0;

            int hr = 0;
            graph = (IGraphBuilder)new FilterGraph();
            ICaptureGraphBuilder2 pBuilder = (ICaptureGraphBuilder2)new CaptureGraphBuilder2();
            hr = pBuilder.SetFiltergraph(graph);            
            Utils.checkHR(hr, "Can't set filtergraph.");

            // add audio input device
            IBaseFilter pAudioInputDevice = CreateDeviceFilter(audioInputDevice);
            hr = graph.AddFilter(pAudioInputDevice, "Audio Input Device");
            Utils.checkHR(hr, "Can't add " + audioInputDevice.Name + " to graph.");

            // add LAME Audio Encoder
            IBaseFilter pLAMEAudioEncoder = (IBaseFilter)Activator.CreateInstance(Type.GetTypeFromCLSID(CLSID_LAMEAudioEncoder));
            hr = graph.AddFilter(pLAMEAudioEncoder, "LAME Audio Encoder");
            Utils.checkHR(hr, "Can't add LAME Audio Encoder to graph.");
/*
            IBaseFilter pCloudRenderer = (IBaseFilter)Activator.CreateInstance(Type.GetTypeFromCLSID(CLSID_CloudStreamRenderer));
            if (pCloudRenderer == null)
                return;

            hr = graph.AddFilter(pCloudRenderer, "Cloud Stream Renderer");
            Utils.checkHR(hr, "Can't add Cloud renderer to graph.");

            ICloudInetControl cloudCtrl = pCloudRenderer as ICloudInetControl;
            if (cloudCtrl == null)
                return;
*/

            IBaseFilter pCloudRenderer = CloudFileWriter.BaseFilter;
            hr = graph.AddFilter(pCloudRenderer, "Cloud Stream Renderer");
            Utils.checkHR(hr, "Can't add Cloud renderer to graph.");
            CloudFileWriter.SetFileName(fileName);

            // connect Audio Input Device and LAME Audio Encoder
            hr = graph.ConnectDirect(Utils.GetFirstOutputPin(pAudioInputDevice), Utils.GetPin(pLAMEAudioEncoder, "XForm In"), null);
            Utils.checkHR(hr, "Can't connect " + audioInputDevice.Name + " and LAME Audio Encoder.");

            // connect LAME Audio Encoder and 
            hr = graph.ConnectDirect(Utils.GetPin(pLAMEAudioEncoder, "XForm Out"), Utils.GetPin(pCloudRenderer, "In"), null);
            Utils.checkHR(hr, "Can't connect LAME Audio Encoder and Cloud Renderer.");
            
            mediaControl = (IMediaControl)graph;
            return 0;
        }

        public void StartCapture()
        {
            int hr = mediaControl.Run();
            Utils.checkHR(hr, "Can't run the graph.");
        }

        public void StopCapture()
        {
            mediaControl.Pause();
            mediaControl.StopWhenReady();
        }
/*
        private void checkHR(int hr, string message)
        {
            if (hr < 0)
            {
                MessageBox.Show(message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                DsError.ThrowExceptionForHR(hr);
            }
        }
 * */
        private IBaseFilter CreateDeviceFilter(DsDevice device)
        {
            Guid guid = typeof(IBaseFilter).GUID;
            object obj;
            device.Mon.BindToObject(null, null, ref guid, out obj);
            return (IBaseFilter)obj;
        }
        /*
        private IPin GetPin(IBaseFilter filter, string pinname)
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

        private IPin GetFirstOutputPin(IBaseFilter filter)
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
         * */
    }
}
