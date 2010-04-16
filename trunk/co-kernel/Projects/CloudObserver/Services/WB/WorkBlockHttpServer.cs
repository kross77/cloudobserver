using System;
using System.IO;
using System.Collections;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Threading;

using CloudObserver.Formats.Audio;
using CloudObserver.Formats.Audio.Mp3;
using Mp3Sharp;

namespace CloudObserver.Services.WB
{
    public class WorkBlockHttpServer
    {
        private int port;
        private TcpListener listener;
        private Thread thread;

        private Dictionary<int, Mp3Stream> streams;

        public string Name;
        public Hashtable ResponseStatuses;

        private uint m_hLameStream = 0;
        private uint m_InputSamples = 0;
        private uint m_OutBufferSize = 0;
        private byte[] m_OutBuffer = null;

        private int bufferSize = 1024;
        private byte[] buffer;

        public bool IsAlive
        {
            get
            {
                return thread.IsAlive;
            }
        }

        public WorkBlockHttpServer(int port)
        {
            this.port = port;
            ResponseStatusInit();

            streams = new Dictionary<int, Mp3Stream>();

            PcmAudioFormat pcmAudioFormat = new PcmAudioFormat(44100, 16, 2);
            Mp3BitRate mp3BitRate = Mp3BitRate.BitRate128;

            WaveFormatEx waveFormat = new WaveFormatEx(pcmAudioFormat.SamplesPerSecond, pcmAudioFormat.BitsPerSample, pcmAudioFormat.Channels);
            Lame_encDll.beInitStream(new BE_CONFIG(new WaveFormat(pcmAudioFormat.SamplesPerSecond, pcmAudioFormat.BitsPerSample, pcmAudioFormat.Channels),
                mp3BitRate, LAME_QUALITY_PRESET.LQP_NORMAL_QUALITY), ref m_InputSamples, ref m_OutBufferSize, ref m_hLameStream);
            m_OutBuffer = new byte[m_OutBufferSize];

            buffer = new byte[bufferSize];
        }

        private void Listen()
        {
            listener = new TcpListener(IPAddress.Any, port);
            listener.Start();

            while (true)
            {
                TcpClient client = listener.AcceptTcpClient();
                WorkBlockHttpRequest request = new WorkBlockHttpRequest(client, this);
                Thread requestThread = new Thread(new ThreadStart(request.Process));
                requestThread.IsBackground = true;
                requestThread.Start();
            }
        }

        public byte[] RequestData(int[] contentIds)
        {
            byte[] pcm = new byte[bufferSize];

            foreach (int contentId in contentIds)
            {
                if (streams.ContainsKey(contentId))
                {
                    int read = streams[contentId].Read(buffer, 0, bufferSize);
                    for (int i = 0; i < read; i++)
                        pcm[i] += (byte)buffer[i];
                }
            }

            uint encodedSize = 0;
            if ((Lame_encDll.EncodeChunk(m_hLameStream, pcm, m_OutBuffer, ref encodedSize) == Lame_encDll.BE_ERR_SUCCESSFUL) && (encodedSize > 0))
            {
                byte[] result = new byte[encodedSize];
                Array.Copy(m_OutBuffer, result, encodedSize);
                return result;
            }
            else
                return null;
        }

        private void ResponseStatusInit()
        {
            ResponseStatuses = new Hashtable();

            ResponseStatuses.Add(200, "200 Ok");
            ResponseStatuses.Add(201, "201 Created");
            ResponseStatuses.Add(202, "202 Accepted");
            ResponseStatuses.Add(204, "204 No Content");

            ResponseStatuses.Add(301, "301 Moved Permanently");
            ResponseStatuses.Add(302, "302 Redirection");
            ResponseStatuses.Add(304, "304 Not Modified");

            ResponseStatuses.Add(400, "400 Bad Request");
            ResponseStatuses.Add(401, "401 Unauthorized");
            ResponseStatuses.Add(403, "403 Forbidden");
            ResponseStatuses.Add(404, "404 Not Found");

            ResponseStatuses.Add(500, "500 Internal Server Error");
            ResponseStatuses.Add(501, "501 Not Implemented");
            ResponseStatuses.Add(502, "502 Bad Gateway");
            ResponseStatuses.Add(503, "503 Service Unavailable");
        }

        public void ProvideStream(int contentId, Stream stream)
        {
            if (!streams.ContainsKey(contentId))
                streams.Add(contentId, new Mp3Stream(stream));
            else
                streams[contentId] = new Mp3Stream(stream);
        }

        public void Start()
        {
            thread = new Thread(new ThreadStart(Listen));
            thread.Start();
        }

        public void Stop()
        {
            listener.Stop();
            thread.Abort();
        }
    }
}
