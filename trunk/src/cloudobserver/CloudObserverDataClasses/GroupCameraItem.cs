using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;

namespace CloudObserverDataClasses
{
    [DataContract]
    public class GroupCameraItem
    {
        [DataMember]
        public int ID { get; set; }

        [DataMember]
        public int CameraID { get; set; }

        [DataMember]
        public int GroupID { get; set; }
    }
}
