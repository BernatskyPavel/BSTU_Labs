using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Runtime.Serialization;
using System.Web;
using System.Xml.Serialization;
using Newtonsoft.Json;

namespace Lab_03.Models
{
    [Table("Students")]
    [DataContract(Name = "student")]
    public class StudentModel : ICloneable
    {
        [Key]
        [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
        [DataMember(Name = "id", IsRequired = false, EmitDefaultValue = false)]
        public int? Id { get; set; }
        [MaxLength(64)]
        [DataMember(Name = "name", IsRequired = false, EmitDefaultValue = false)]
        public string Name { get; set; }
        [MaxLength(16)]
        [DataMember(Name = "phone", IsRequired = false, EmitDefaultValue = false)]
        public string Phone { get; set; }

        [NotMapped]
        [DataMember(Name = "_links", IsRequired = false, EmitDefaultValue = false)]
        public List<LinkModel> Links { get; set; }

        public object Clone()
        {
            StudentModel clone = new StudentModel();
            clone.Id = this.Id;
            clone.Name = (string)this.Name.Clone();
            clone.Phone = (string)this.Phone.Clone();
            return clone;
        }

        public string Concat()
        {
            return $@"{this.Id}{this.Name}{this.Phone}";
        }
    }
}