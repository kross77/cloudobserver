using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;
using CloudObserverDatabaseLibrary;

namespace WcfServiceTest
{
    // NOTE: If you change the class name "Service1" here, you must also update the reference to "Service1" in App.config.
    public class ServiceTest : IServiceTest
    {
        CloudObserverDatabase database;

        private void CheckConnection()
        {
            if (database == null) database = new CloudObserverDatabase();
        }

        public string GetData(int value)
        {
            return string.Format("You entered: {0}", value);
        }

        public CompositeType GetDataUsingDataContract(CompositeType composite)
        {
            if (composite.BoolValue)
            {
                composite.StringValue += "Suffix";
            }
            return composite;
        }

        public bool IsEmailRegistered(string email)
        {
            CheckConnection();
            return database.IsEmailRegistered(email);
        }
    }
}
