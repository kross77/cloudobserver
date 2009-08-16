using System;
using System.Linq;

namespace CloudObserver.Databases
{
    public class TemplateDatabase : Database
    {
        private new TemplateDataClassesDataContext database;

        public TemplateDatabase()
        {
            database = new TemplateDataClassesDataContext();

            InitializeComponent();
        }

        public TemplateDatabase(string serverName, string databaseName)
        {
            database = new TemplateDataClassesDataContext(GetConnectionString(serverName, databaseName));

            InitializeComponent();
        }

        private void InitializeComponent()
        {
            if (!database.DatabaseExists())
                database.CreateDatabase();
        }
    }
}