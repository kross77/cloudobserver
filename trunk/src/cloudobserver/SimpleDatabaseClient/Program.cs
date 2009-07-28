using System;
using CloudObserverDatabaseLibrary;

namespace SimpleDatabaseClient
{
    class Program
    {
        private const string DEFAULT_DATABASE_CONNECTION = @"Data Source=.\sqlexpress;Initial Catalog=CloudObserverDatabase;Integrated Security=True";

        static void Main(string[] args)
        {
            Console.WriteLine("Connecting to Cloud Observer database...");
            CloudObserverDatabase database = new CloudObserverDatabase(DEFAULT_DATABASE_CONNECTION);
            Console.Write("Connection succeed. Enter email to check: ");
            Console.WriteLine("This email " + (database.UserIsEmailAvailable(Console.ReadLine()) ? "is" : "is not") + " available.");
            Console.Write("Press any key to exit...");
            Console.ReadKey();
        }
    }
}