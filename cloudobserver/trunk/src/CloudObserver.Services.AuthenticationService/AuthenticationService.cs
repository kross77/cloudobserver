using System;
using CloudObserver.Databases;

namespace CloudObserver.Services
{
    public class AuthenticationService : Service, AuthenticationServiceContract
    {
        private AccountsDatabase accountsDatabase;
        private string serverName;
        private string databaseName;
        private bool defaultConnection = true;

        public AuthenticationService(string serverName, string databaseName)
        {
            this.serverName = serverName;
            this.databaseName = databaseName;
            defaultConnection = false;
        }

        public new void SetControllerServiceUri(string controllerServiceUri)
        {
            base.SetControllerServiceUri(controllerServiceUri);
            if (defaultConnection) accountsDatabase = new AccountsDatabase(controllerServiceUri);
            else accountsDatabase = new AccountsDatabase(controllerServiceUri, serverName, databaseName);
        }

        // users
        public bool UserCheckEmailAvailability(string email)
        {
            return accountsDatabase.UserCheckEmailAvailability(email);
        }

        public bool UserLogin(string email, string password)
        {
            return accountsDatabase.UserLogin(email, password);
        }

        public int UserRegister(string email, string password, string name, string description, byte[] icon)
        {
            return accountsDatabase.UserRegister(email, password, name, description, icon);
        }
    }
}