using System;
using System.Data.Linq;

namespace CloudObserver.Databases
{
    public abstract class Database : Object
    {
        protected DataContext database;
        
        protected string GetConnectionString(string serverName, string databaseName)
        {
            return "Data Source=" + serverName + ";Initial Catalog=" + databaseName + ";Integrated Security=True";
        }

        public void DeleteDatabase()
        {
            database.DeleteDatabase();
        }
    }
}