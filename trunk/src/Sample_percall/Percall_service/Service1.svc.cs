using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;

namespace Percall_service
{
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.PerCall)]
    class MyService : IMyContract, IDisposable
    {
        int m_Counter = 0;

        MyService()
        {
            
        }
        public string MyMethod()
        {
            m_Counter++;
            return ("Counter = " + m_Counter.ToString());
        }
        public void Dispose()
        {
            
        }
    }

}
