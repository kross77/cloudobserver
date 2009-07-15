using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;

namespace CloudObserverDataClasses
{
    [DataContract]
    public class FrameItem
    {
        [DataMember]
        public int FrameID { get; set; }

        [DataMember]
        public int CameraID { get; set; }

        [DataMember]
        public byte[] ContentPath { get; set; }

        [DataMember]
        public string Marker { get; set; }
    }
}
