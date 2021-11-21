using Lab_03.Models;
using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Web;

namespace Lab_03.Context
{
    public class PSQLStudentContext : DbContext
    {
        public DbSet<StudentModel> Students { get; set; }
        public PSQLStudentContext() : base("PSQLStudentContext")
        {
            
        }
        protected override void OnModelCreating(DbModelBuilder modelBuilder)
        {
            modelBuilder.HasDefaultSchema("public");
            base.OnModelCreating(modelBuilder);
        }

    }
}