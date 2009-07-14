using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WcfClientTest
{
    class Program
    {
        static void Main(string[] args)
        {
            ServiceReferenceTest.ServiceTestClient proxy = new ServiceReferenceTest.ServiceTestClient();
            Console.Write("Email: ");
            Console.WriteLine("This email " + (proxy.IsEmailRegistered(Console.ReadLine()) ? "is" : "is not") + " registered.");
            Console.ReadKey();
        }
    }
}
