using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;

namespace CloudObserverDataClasses
{
    [DataContract]
    public class GroupMemberItem
    {
        [DataMember]
        public int ID { get; set; }

        [DataMember]
        public int UserID { get; set; }

        [DataMember]
        public int GroupID { get; set; }

        [DataMember]
        public int Privileges { get; set; }
    }
}
