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
    public class UserItem
    {
        [DataMember]
        public int UserID { get; set; }

        [DataMember]
        public string Email { get; set; }

        [DataMember]
        public string Password { get; set; }

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
