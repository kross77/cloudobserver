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
    class CameraItem
    {
        [DataMember]
        public int CameraID { get; set; }

        [DataMember]
        public string Path { get; set; }

        [DataMember]
        public string Name { get; set; }

        [DataMember]
        public XElement Description { get; set; }

        [DataMember]
        public Bitmap Icon { get; set; }

        [DataMember]
        public DateTime RegistrationDate { get; set; }
    }
}
