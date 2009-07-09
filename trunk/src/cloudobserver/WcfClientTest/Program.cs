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
            Console.WriteLine(proxy.GetData(123));
            Console.ReadKey();
        }
    }
}
