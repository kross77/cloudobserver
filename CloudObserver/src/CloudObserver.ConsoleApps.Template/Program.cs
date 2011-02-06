using System;

namespace CloudObserver.ConsoleApps.Template
{
    class Program
    {
        static void Main(string[] args)
        {
            if ((args.Length > 0) && (args[0] == "/?"))
            {
                Console.Write("Usage: CloudObserver.ConsoleApps.Template");
                return;
            }
        }
    }
}