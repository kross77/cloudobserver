using System;

namespace CloudObserverTemplateServiceLibrary
{
    public class CloudObserverTemplateService : ICloudObserverTemplateService
    {
        public string Echo(string input)
        {
            return input;
        }
    }
}