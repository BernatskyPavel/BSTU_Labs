using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Web;
using System.IO;
using Newtonsoft.Json;
using System.Threading;
using System.Net;

namespace Lab_04.Models
{
    public class DictContext: DbContext
    {
        public DbSet<Record> Records { get; set; }
        public DictContext() : base("DictContext")
        {
        }
        protected override void OnModelCreating(DbModelBuilder modelBuilder)
        {
            modelBuilder.HasDefaultSchema("public");
        }
    }
}