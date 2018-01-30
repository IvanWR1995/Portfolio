﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated from a template.
//
//     Manual changes to this file may cause unexpected behavior in your application.
//     Manual changes to this file will be overwritten if the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace ClientDBEditor
{
    using System;
    using System.Data.Entity;
    using System.Data.Entity.Infrastructure;
    using System.Data.Entity.Core.Objects;
    using System.Linq;
    
    public partial class GuitarsDBModelEntities : DbContext
    {
        public GuitarsDBModelEntities(string ConnectionString)
            : base(ConnectionString)
        {
        }
        public GuitarsDBModelEntities()
            : base("name=GuitarsDBModelEntities")
        {
        }
    
        protected override void OnModelCreating(DbModelBuilder modelBuilder)
        {
            throw new UnintentionalCodeFirstException();
        }
    
        public virtual DbSet<TableAdress> TableAdresses { get; set; }
        public virtual DbSet<TableColorSetsGuitar> TableColorSetsGuitars { get; set; }
        public virtual DbSet<TableContact> TableContacts { get; set; }
        public virtual DbSet<TableDescriptionGuitar> TableDescriptionGuitars { get; set; }
        public virtual DbSet<TableExGuitarColor> TableExGuitarColors { get; set; }
        public virtual DbSet<TableGuitar> TableGuitars { get; set; }
        public virtual DbSet<TableManufacturerInfo> TableManufacturerInfoes { get; set; }
        public virtual DbSet<TablePhoneNumber> TablePhoneNumbers { get; set; }
    
        public virtual int CreateProc()
        {
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction("CreateProc");
        }
    
        public virtual int CreateBackup()
        {
            return ((IObjectContextAdapter)this).ObjectContext.ExecuteFunction("CreateBackup");
        }
    }
}