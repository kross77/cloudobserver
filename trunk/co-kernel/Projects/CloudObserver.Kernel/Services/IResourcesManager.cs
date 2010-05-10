﻿using System.ServiceModel;

namespace CloudObserver.Kernel.Services
{
    [ServiceContract]
    public interface IResourcesManager
    {
        [OperationContract]
        bool StartCloudObserver();

        [OperationContract]
        string HostWorkBlock();

        [OperationContract]
        int GetFreePort();
    }
}
