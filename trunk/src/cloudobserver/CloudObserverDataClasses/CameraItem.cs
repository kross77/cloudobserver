using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;

namespace CloudObserverDataClasses
{
    [DataContract]
    public class CameraItem
    {
        [DataMember]
        public int CameraID { get; set; }

        [DataMember]
        public string Path { get; set; }

        [DataMember]
        public string Name { get; set; }

        [DataMember]
        public string Description { get; set; }

        [DataMember]
        public byte[] IconPath { get; set; }

        [DataMember]
        public DateTime RegistrationDate { get; set; }
    }
}
