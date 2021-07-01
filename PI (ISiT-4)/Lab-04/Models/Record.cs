using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Web;

namespace Lab_04.Models
{
    [Table("Records")]
    public class Record
    {
        [Required]
        [Key]
        public Guid Id { get; set; }
        [Required]
        [MaxLength(64)]
        public string Name { get; set; }
        [Required]
        [MaxLength(64)]
        public string Lastname { get; set; }
        [Required]
        [MaxLength(16)]
        public string Phone{ get; set; }

        public Record()
        {
            this.Id = Guid.NewGuid();
        }
    }
}