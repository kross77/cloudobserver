using System;
using System.Net;

using Mp3Sharp;
using Microsoft.DirectX.DirectSound;

namespace Multimedia
{
    public class Player
    {
        private string uri;
        private Device device;
        private StreamedMp3Sound streamedMp3Sound = null;

        public Player(string uri, Device device)
        {
            this.uri = uri;
            this.device = device;
        }

        public void Play()
        {
            streamedMp3Sound = new StreamedMp3Sound(device, new Mp3Stream(WebRequest.Create(uri).GetResponse().GetResponseStream()));
            streamedMp3Sound.Play();
        }

        public void Stop()
        {
            streamedMp3Sound.Stop();
        }
    }
}