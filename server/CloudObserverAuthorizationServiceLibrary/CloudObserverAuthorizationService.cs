using System;
using CloudObserverDatabaseLibrary;

namespace CloudObserverAuthorizationServiceLibrary
{
    public class CloudObserverAuthorizationService : ICloudObserverAuthorizationService
    {
        private CloudObserverDatabase database = null;

        public CloudObserverAuthorizationService()
        {
            database = new CloudObserverDatabase();
        }

        public CloudObserverAuthorizationService(string databaseConnection)
        {
            database = new CloudObserverDatabase(databaseConnection);
        }

        // users
        public bool UserIsEmailAvailable(string email)
        {
            return database.UserIsEmailAvailable(email);
        }

        public bool UserLogin(string email, string password)
        {
            return database.UserLogin(email, password);
        }

        public int UserAdd(string email, string password, string name, string description, byte[] icon)
        {
            return database.UserAdd(email, password, name, description, icon);
        }
    }
}