using System;
using System.ServiceModel;

namespace CloudObserver.Services
{
    [ServiceContract]
    public interface TestSoundServiceContract : AbstractServiceContract
    {
        [OperationContract]
        bool IsSoundDataUpdated();

        [OperationContract(IsOneWay = true)]
        void WriteSoundData(byte[] soundData);

        [OperationContract]
        byte[] ReadSoundData();
    }
}