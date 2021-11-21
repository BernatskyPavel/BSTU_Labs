using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Web;
using System.Xml.Serialization;

namespace Lab_03.Models
{
    [DataContract(Name = "_error")]
    public class ErrorModel
    {
        [DataMember(Name = "_status_code", IsRequired = false, EmitDefaultValue = false)]
        public int Status { get; set; }
        [DataMember(Name = "_message", IsRequired = false, EmitDefaultValue = false)]
        public string Message { get; set; }
        [DataMember(Name = "_href", IsRequired = false, EmitDefaultValue = false)]
        public string Url { get; set; }
    }
}