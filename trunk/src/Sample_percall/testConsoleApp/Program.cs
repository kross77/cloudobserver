using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using testConsoleApp.perCallService;

namespace testConsoleApp
{
    class Program
    {
        static void Main(string[] args)
        {
            perCallService.MyContractClient proxy = new perCallService.MyContractClient();
            System.Console.WriteLine(proxy.MyMethod());
            System.Console.WriteLine(proxy.MyMethod());
            System.Console.WriteLine("As you can see, every time the new instance of service object is used.");
            return;
        }
    }
}
