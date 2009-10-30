using System;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;

namespace CloudObserver.Services
{
    public class DebugServiceHost : ServiceHost
    {
        public DebugServiceHost(Type serviceContractType, Binding binding, object singletonInstance, params Uri[] baseAddresses) : base(singletonInstance, baseAddresses)
        {
            ServiceMetadataBehavior serviceMetadataBehavior = this.Description.Behaviors.Find<ServiceMetadataBehavior>();
            if (serviceMetadataBehavior == null)
            {
                serviceMetadataBehavior = new ServiceMetadataBehavior();
                serviceMetadataBehavior.HttpGetEnabled = true;
                this.Description.Behaviors.Add(serviceMetadataBehavior);
            }
            else
                serviceMetadataBehavior.HttpGetEnabled = true;

            ServiceDebugBehavior serviceDebugBehavior = this.Description.Behaviors.Find<ServiceDebugBehavior>();
            if (serviceDebugBehavior == null)
            {
                serviceDebugBehavior = new ServiceDebugBehavior();
                serviceDebugBehavior.IncludeExceptionDetailInFaults = true;
                this.Description.Behaviors.Add(serviceDebugBehavior);
            }
            else
                serviceDebugBehavior.IncludeExceptionDetailInFaults = true;

            this.AddServiceEndpoint(serviceContractType, binding, "");
        }
    }
}