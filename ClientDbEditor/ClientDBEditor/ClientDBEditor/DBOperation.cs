
namespace ClientDBEditor
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;
    using System.Threading.Tasks;
    using System.Data;
     using System.Data.Entity;
    using System.Data.Entity.Migrations;
    using System.Data.Entity.Core;
    class DBOperation : GuitarsDBModelEntities
    {
        string User;
        string PWD;
        Dictionary<int, DbSet>  TablePage;
        public DBOperation(string ConnectionString)
            :base(ConnectionString)
        {
 
        }
        public DBOperation(string User, string Password)
            : base(@"metadata=res://*/GuitarsDBModel.csdl|res://*/GuitarsDBModel.ssdl|res://*/GuitarsDBModel.msl;
                    provider=System.Data.SqlClient;provider connection string='data source=PC\SQLEXPRESS;
                    initial catalog=Database guitars;MultipleActiveResultSets=True;
                    App=EntityFramework;UID=" + User +";PWD=" + Password + "'")
          
         {
             TablePage = new Dictionary<int, DbSet>();
             TablePage.Add(0, base.TableGuitars);
             TablePage.Add(1, base.TableDescriptionGuitars);
             TablePage.Add(2, base.TableManufacturerInfoes);
             TablePage.Add(3, base.TableContacts);
             TablePage.Add(4, base.TableAdresses);
             TablePage.Add(5, base.TablePhoneNumbers);
             TablePage.Add(6, base.TableColorSetsGuitars);
             TablePage.Add(7, base.TableExGuitarColors);
             this.User = User;
             this.PWD = Password;
         }
        public string Login
        {
            get { return User; }
        }
        public string Password
        {
            get { return PWD; }
        }
        public Object GetNumberTable(int NumberTab)
        {
            switch (NumberTab)
            {
                case 0:
                    return TableGuitars;
                case 1:
                    return TableDescriptionGuitars;
                case 2:
                    return TableManufacturerInfoes;
                case 3:
                    return TableContacts;
                case 4:
                    return TableAdresses;
                case 5:
                    return TablePhoneNumbers;
                case 6:
                    return TableColorSetsGuitars;
                case 7:
                    return TableExGuitarColors;
            }
            return null;
        }
        public DBOperation()
        {
           
            TablePage = new Dictionary<int, DbSet>();
            TablePage.Add(0, base.TableGuitars);
            TablePage.Add(1, base.TableDescriptionGuitars);
            TablePage.Add(2, base.TableManufacturerInfoes);
            TablePage.Add(3, base.TableContacts);
            TablePage.Add(4, base.TableAdresses);
            TablePage.Add(5, base.TablePhoneNumbers);
            TablePage.Add(6, base.TableColorSetsGuitars);
            TablePage.Add(7, base.TableExGuitarColors);
            
        }

        public IEnumerable<TableGuitar>  TableGuitars
        {
            get {
                
                base.TableGuitars.Load();
                return base.TableGuitars.Local.ToBindingList();
            }
        }
        public IEnumerable<TableDescriptionGuitar> TableDescriptionGuitars
        {
            get {
                base.TableDescriptionGuitars.Load();
                return base.TableDescriptionGuitars.Local.ToBindingList(); 
            }
        }
        public IEnumerable<TableManufacturerInfo> TableManufacturerInfoes
        {
            get {
                base.TableManufacturerInfoes.Load();
                return base.TableManufacturerInfoes.Local.ToBindingList(); 
            }
        }
        public IEnumerable<TableContact> TableContacts
        {
            get {
                base.TableContacts.Load();
                return base.TableContacts.Local.ToBindingList(); 
            }
        }
        public IEnumerable<TableAdress> TableAdresses
        {
            get {
                base.TableAdresses.Load();
                return base.TableAdresses.Local.ToBindingList(); 
            }
        }
        public IEnumerable<TablePhoneNumber> TablePhoneNumbers
        {
            get {
                base.TablePhoneNumbers.Load();
                return base.TablePhoneNumbers.Local.ToBindingList(); 
            }
        }
        public IEnumerable<TableColorSetsGuitar> TableColorSetsGuitars
        {
            get {
                    base.TableColorSetsGuitars.Load();
                    return base.TableColorSetsGuitars.Local.ToBindingList();
            }
        }
        public IEnumerable<TableExGuitarColor> TableExGuitarColors
        {
            get {
                    base.TableExGuitarColors.Load();
                    return base.TableExGuitarColors.Local.ToBindingList();
            }
        }
        public void SaveChanges()
        {
            base.SaveChanges();
        }
        public void Delete<TPrimaryKey>(int Page, TPrimaryKey PKValue)
        {
            var ItemToRm = TablePage[Page].Find(PKValue);
            if (ItemToRm != null)
                TablePage[Page].Remove(ItemToRm);
                
            
        }
    }
}
