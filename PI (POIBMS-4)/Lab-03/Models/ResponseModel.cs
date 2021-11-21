using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Runtime.Serialization;
using System.Web;
using System.Xml.Serialization;

namespace Lab_03.Models
{
    [DataContract(Name = "_response")]
    public class ResponseModel<T> where T : class
    {
        [DataMember(Name = "item", IsRequired = false, EmitDefaultValue = false, Order = 0)]
        public T Object { get; set; }
        [DataMember(Name = "collection", IsRequired = false, EmitDefaultValue = false, Order = 1)]        
        public IEnumerable<T> Collection { get; set; }
        [DataMember(Name = "_error", IsRequired = false, EmitDefaultValue = false, Order = 2)]
        public ErrorModel Error { get; set; }
        [Required]
        [DataMember(Name = "_links", IsRequired = true, Order = 3)]
        public IEnumerable<LinkModel> Links { get; set; }

        public ResponseModel() {
            Object = null;
            Collection = null;
            Error = null;
            Links = null;
        }
    }
}