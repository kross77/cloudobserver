using System;
using System.Threading;

namespace CloudObserver.ConsoleApps.Delay
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length == 1)
                Thread.Sleep(Int32.Parse(args[0]));
            else
                Console.Write("Usage: CloudObserver.ConsoleApps.Delay <milliseconds>");
        }
    }
}