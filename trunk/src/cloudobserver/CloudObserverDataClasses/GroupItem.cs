using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;

namespace CloudObserverDataClasses
{
    [DataContract]
    public class GroupItem
    {
        [DataMember]
        public int GroupID { get; set; }

        [DataMember]
        public string Name { get; set; }

        [DataMember]
        public string Description { get; set; }

        [DataMember]
        public byte[] IconPath { get; set; }

        [DataMember]
        public int Privacy { get; set; }

        [DataMember]
        public DateTime RegistrationDate { get; set; }
    }
}
