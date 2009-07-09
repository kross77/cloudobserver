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
    class FrameItem
    {
        [DataMember]
        public int FrameID { get; set; }

        [DataMember]
        public int CameraID { get; set; }

        [DataMember]
        public Bitmap Content { get; set; }

        [DataMember]
        public XElement Marker { get; set; }
    }
}
