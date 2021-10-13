using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Web;
using System.Xml.Serialization;

namespace Lab_03.Models
{
    [DataContract(Name = "_link")]
    public class LinkModel
    {
        [DataMember(Name = "_action", IsRequired = false, EmitDefaultValue = false)]
        public string Action { get; set; }
        [DataMember(Name = "_method", IsRequired = false, EmitDefaultValue = false)]
        public string Method { get; set; }
        [DataMember(Name = "_href", IsRequired = false, EmitDefaultValue = false)]
        public string Url { get; set; }
    }
}