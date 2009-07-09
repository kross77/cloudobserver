using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Linq;
using System.Drawing;
using System.Runtime.Serialization;

namespace CloudObserverDataClasses
{
    [DataContract]
    class GroupItem
    {
        [DataMember]
        public int GroupID { get; set; }

        [DataMember]
        public string Name { get; set; }

        [DataMember]
        public XElement Description { get; set; }

        [DataMember]
        public Bitmap Icon { get; set; }

        [DataMember]
        public bool Privacy { get; set; }

        [DataMember]
        public DateTime RegistrationDate { get; set; }
    }
}
