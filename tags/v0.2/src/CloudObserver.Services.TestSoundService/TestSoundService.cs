using System;
using System.IO;
using System.ServiceModel;

namespace CloudObserver.Services
{
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
    public class TestSoundService : AbstractService, TestSoundServiceContract
    {
        private bool updated = false;
        private const int BUFFER_SIZE = 88200;
        private byte[] buffer;

        public TestSoundService()
        {
            buffer = new byte[BUFFER_SIZE];
        }

        public bool IsSoundDataUpdated()
        {
            return updated;
        }

        public void WriteSoundData(byte[] soundData)
        {
            buffer = soundData;
            updated = true;
        }

        public byte[] ReadSoundData()
        {
            updated = false;
            return buffer;
        }
    }
}