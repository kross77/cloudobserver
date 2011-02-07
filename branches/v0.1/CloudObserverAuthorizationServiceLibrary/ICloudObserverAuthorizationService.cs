using System;
using System.ServiceModel;

namespace CloudObserverAuthorizationServiceLibrary
{
    [ServiceContract]
    public interface ICloudObserverAuthorizationService
    {
        [OperationContract]
        bool UserIsEmailAvailable(string email);

        [OperationContract]
        bool UserLogin(string email, string password);

        [OperationContract]
        int UserAdd(string email, string password, string name, string description, byte[] icon);
    }
}