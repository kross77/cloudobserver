using System;
using System.Text;
using System.Threading;
using System.Net;
using System.Net.Sockets;
using System.Collections.Generic;

using CloudObserver.Formats;
using CloudObserver.Formats.Audio;
using CloudObserver.Formats.Audio.Mp3;
using CloudObserver.Capture.DirectSound;

namespace CloudObserver.Multimedia
{
    public class Transmitter
    {
        private const int port = 4773;
        private const string responseHeader = "HTTP/1.0 200 OK\r\nContent-Type: audio/mpeg\r\n\r\n";

        private bool transmitting = false;
        private int connections = 0;
        private Thread listenerThread = null;
        private TcpListener listener = null;
        private List<NetworkStream> clients = null;
        private DirectSoundCapture directSoundCapture = null;

        private uint m_hLameStream = 0;
        private uint m_InputSamples = 0;
        private uint m_OutBufferSize = 0;
        private byte[] m_OutBuffer = null;

        public int Connections
        {
            get { return connections; }
            set
            {
                connections = value;
                ConnectionsUpdated.Invoke(this, new ConnectionsUpdatedEventArgs(value));
            }
        }

        public event ConnectionsUpdatedEventHandler ConnectionsUpdated;

        public Transmitter()
        {
            listener = new TcpListener(IPAddress.Any, port);
            clients = new List<NetworkStream>();
            listenerThread = new Thread(new ThreadStart(ListenerLoop));
            listenerThread.IsBackground = true;
        }

        public void Start(DirectSoundCaptureDevice directSoundCaptureDevice, PcmAudioFormat pcmAudioFormat, Mp3BitRate mp3BitRate)
        {
            if (!transmitting)
            {
                transmitting = true;

                WaveFormatEx waveFormat = new WaveFormatEx(pcmAudioFormat.SamplesPerSecond, pcmAudioFormat.BitsPerSample, pcmAudioFormat.Channels);
                Lame_encDll.beInitStream(new BE_CONFIG(new WaveFormat(pcmAudioFormat.SamplesPerSecond, pcmAudioFormat.BitsPerSample, pcmAudioFormat.Channels),
                    mp3BitRate, LAME_QUALITY_PRESET.LQP_NORMAL_QUALITY), ref m_InputSamples, ref m_OutBufferSize, ref m_hLameStream);
                m_OutBuffer = new byte[m_OutBufferSize];

                directSoundCapture = new DirectSoundCapture(pcmAudioFormat, directSoundCaptureDevice);
                directSoundCapture.ChunkCaptured += new EventHandler<CloudObserver.Capture.ChunkCapturedEventArgs>(ChunkCaptured);
                directSoundCapture.Start();

                listener.Start();
                listenerThread.Start();
            }
        }

        public void Stop()
        {
            if (directSoundCapture != null)
            {
                transmitting = false;

                directSoundCapture.Stop();
                directSoundCapture = null;
                foreach (NetworkStream client in clients)
                    client.Close();
                clients.Clear();
                listener.Stop();
                listenerThread = new Thread(new ThreadStart(ListenerLoop));
                Connections = 0;
            }
        }

        private void ChunkCaptured(object sender, CloudObserver.Capture.ChunkCapturedEventArgs e)
        {
            uint EncodedSize = 0;
            if (Lame_encDll.EncodeChunk(m_hLameStream, e.ChunkData, m_OutBuffer, ref EncodedSize) == Lame_encDll.BE_ERR_SUCCESSFUL)
                if (EncodedSize > 0)
                {
                    List<NetworkStream> deadClients = new List<NetworkStream>();
                    foreach (NetworkStream client in clients)
                        try
                        {
                            client.Write(m_OutBuffer, 0, (int)EncodedSize);
                        }
                        catch (Exception)
                        {
                            deadClients.Add(client);
                            Connections--;
                        }
                    foreach (NetworkStream deadClient in deadClients)
                        clients.Remove(deadClient);
                    deadClients.Clear();
                }
        }

        private void ListenerLoop()
        {
            while (transmitting)
            {
                try
                {
                    NetworkStream client = listener.AcceptTcpClient().GetStream();
                    byte[] header = Encoding.UTF8.GetBytes(responseHeader);
                    client.Write(header, 0, header.Length);
                    clients.Add(client);
                    Connections++;
                }
                catch (Exception)
                {
                }
            }
        }
    }
}