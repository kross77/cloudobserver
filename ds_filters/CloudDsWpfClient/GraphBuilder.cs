using System;
using System.Windows.Forms;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.Runtime.InteropServices.ComTypes;
using DirectShowLib;
using System.Xml;

using CloudObserver.DirectShow;

using CloudObserver.DirectShow.Filters;
using System.Threading;
using System.Net;
using System.Net.Sockets;
using System.IO;

namespace CloudObserver.DirectShow.Graphs
{
    public static class CloudGraphFactory
    {
        public static ICloudGraphBuilder Create(XmlDocument xDoc)
        {
            XmlNodeList xBuilder = xDoc.GetElementsByTagName("Builder");
            XmlNodeList xFileName = xDoc.GetElementsByTagName("FileName");
            XmlNodeList xAudioDevName = xDoc.GetElementsByTagName("AudioInput");
            XmlNodeList xHostAddress = xDoc.GetElementsByTagName("HostAddress");
            XmlNodeList xHostPort = xDoc.GetElementsByTagName("HostPort");
            switch (xBuilder[0].InnerText)
            {
                case "CloudFileWriter":                    
                    FileWriterGraphBuilder builderFW = new FileWriterGraphBuilder();
                    builderFW.CreateFilter(GetAudioInputDevicesByName(xAudioDevName[0].InnerText), xFileName[0].InnerText);
                    return (ICloudGraphBuilder)builderFW;
                case "CloudSocketRenderer":
                    CloudSocketRendererGraphBuilder builderSR = new CloudSocketRendererGraphBuilder();
                    builderSR.CreateFilter(GetAudioInputDevicesByName(xAudioDevName[0].InnerText), xFileName[0].InnerText,
                        xHostAddress[0].InnerText, Int32.Parse(xHostPort[0].InnerText));
                    return (ICloudGraphBuilder)builderSR;
                case "CloudClientToServer":
                    return (ICloudGraphBuilder)new CloudClientToServerGraphBuilder();
                default:
                    return null;
            }
        }
        private static DsDevice []audioInputDevices = null;
        private static List<string> listNames = new List<string>();
        public static  List<string> EnumerateAudioInputDevices()
        {
            if (null == audioInputDevices)
            {
                audioInputDevices = DsDevice.GetDevicesOfCat(FilterCategory.AudioInputDevice);

                foreach (DsDevice device in audioInputDevices)
                {
                    listNames.Add(device.Name);
                }

            }
            return listNames;
        }
        private static DsDevice GetAudioInputDevicesByName(string name)
        {
            if (null == audioInputDevices)
            {
                return null;

            }
            foreach (DsDevice device in audioInputDevices)
            {
                if (device.Name == name)
                    return device;
            }
            return null;
        }
    }

    public interface ICloudGraphBuilder
    {
        int Start();
        int Stop();
    }

    class CloudGraphBuilder : ICloudGraphBuilder
    {
        protected Guid CLSID_LAMEAudioEncoder = new Guid("{B8D27088-FF5F-4B7C-98DC-0E91A1696286}"); // lame.ax
        protected IGraphBuilder graph = (IGraphBuilder)new FilterGraph();
        protected IMediaControl mediaControl = null;

        public virtual int Start()
        {
            int hr = mediaControl.Run();
            Utils.checkHR(hr, "Can't run the graph.");
            return 0;
        }

        public virtual int Stop()
        {
            mediaControl.Pause();
            mediaControl.StopWhenReady();
            return 0;
        }

        protected IBaseFilter CreateDeviceFilter(DsDevice device)
        {
            Guid guid = typeof(IBaseFilter).GUID;
            object obj;
            device.Mon.BindToObject(null, null, ref guid, out obj);
            return (IBaseFilter)obj;
        }
    }

    class FileWriterGraphBuilder : CloudGraphBuilder
    {        

        public FileWriterGraphBuilder()
        {
        }
        public int CreateFilter(DsDevice audioInputDevice, string fileName)
        {
            int hr = 0;

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
    }
    class CloudSocketRendererGraphBuilder : CloudGraphBuilder
    {
        private Thread thread = null;
        private IPAddress ipAddr = null;
        private TcpListener tcpListener = null;
        private Socket socket = null;
        private string filePath = null;
        private string hostAddr = null;
        private int hostPort;

        public int CreateFilter(DsDevice audioInputDevice, string fileName, string hostAddress, int port)
        {
            int hr = 0;
            filePath = fileName;
            hostAddr = hostAddress;
            hostPort = port;

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


            IBaseFilter pCloudRenderer = CloudStreamRenderer.BaseFilter;
            hr = graph.AddFilter(pCloudRenderer, "Cloud Stream Renderer");
            Utils.checkHR(hr, "Can't add Cloud renderer to graph.");
            CloudStreamRenderer.SetAddress(hostAddress, port);

            // connect Audio Input Device and LAME Audio Encoder
            hr = graph.ConnectDirect(Utils.GetFirstOutputPin(pAudioInputDevice), Utils.GetPin(pLAMEAudioEncoder, "XForm In"), null);
            Utils.checkHR(hr, "Can't connect " + audioInputDevice.Name + " and LAME Audio Encoder.");

            // connect LAME Audio Encoder and 
            hr = graph.ConnectDirect(Utils.GetPin(pLAMEAudioEncoder, "XForm Out"), Utils.GetPin(pCloudRenderer, "In"), null);
            Utils.checkHR(hr, "Can't connect LAME Audio Encoder and Cloud Renderer.");

            mediaControl = (IMediaControl)graph;
            return 0;
        }

        public CloudSocketRendererGraphBuilder()
        {
        }
        
        private int OpenSocket(string addr, int port)
        {
            this.ipAddr = IPAddress.Parse(addr);
            tcpListener = new TcpListener(this.ipAddr, port);
            return 0;
        }
        
        private int CloseSocket()
        {
            socket.Close();
            tcpListener.Stop();
            return 0;
        }

        private int StartSocket()
        {
            /* Start Listeneting at the specified port */
            tcpListener.Start();
            socket = tcpListener.AcceptSocket();
            return 0;
        }

        private void ThreadFunction()
        {
            byte[] b = new byte[1024];
            if (0 != StartSocket())
            {
                return;
            }
            using (FileStream sw = File.Create(filePath))
            {

                while (true)
                {
                    int k = socket.Receive(b);
                    if (k == 0)
                        break;
                    else
                        sw.Write(b, 0, k);
                }
                sw.Close();
            }
            CloseSocket();
        }

        public override int Start()
        {
            if (0 != OpenSocket(hostAddr, hostPort))
            {
                return -1;
            }
            thread = new Thread(ThreadFunction);
            thread.Start();

            return base.Start();
        }

        public override int Stop()
        {
            CloseSocket();            
            thread.Abort();

            return base.Stop();
        }
    }
    class CloudClientToServerGraphBuilder : CloudGraphBuilder
    {
        public CloudClientToServerGraphBuilder()
        {
        }
    }
}
