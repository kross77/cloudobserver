using System;
using System.ServiceModel;

namespace CloudObserver.Services
{
    [ServiceContract]
    public interface AuthenticationServiceContract : ServiceContract
    {
        [OperationContract]
        bool UserCheckEmailAvailability(string email);

        [OperationContract]
        bool UserLogin(string email, string password);

        [OperationContract]
        int UserRegister(string email, string password, string name, string description, byte[] icon);
    }
}