using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Data.SqlClient;
using System.Data.Entity.Validation;
using System.Data.Entity.Infrastructure;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ClientDBEditor
{
    public partial class Form1 : Form
    {
        string Path = @"C:\Users\Шумаков Иван\Documents\Visual Studio 2013\Projects\ClientDBEditor\ClientDBEditor\Properties\";
        Dictionary<string, Image> ImageCollection;
        AuthorizationForm LogInDialog;
        DBOperation context;// = new DBOperation();
        DataGridView CurrentDataGrid;
            
        bool IsUpdated = true;
        public Form1()
        {
            InitializeComponent();
        }
        private void ResetDataBinding()
        {
            DataGridGuitars.DataSource = null;
            DataGridAddress.DataSource = null;
            DataGridDecscriptGuitars.DataSource = null;
            DataGridManufactInfo.DataSource = null;
            DataGridContacts.DataSource = null;
            DataGridPhones.DataSource = null;
            DataGridGuitarsColoring.DataSource = null;
            DataGridColorSchemes.DataSource = null;
        }
        private void DataBinding()
        {
            DataGridGuitars.DataSource                  = context.TableGuitars;
            DataGridGuitars.RowEnter                    += DataGrid_RowEnter;
            DataGridGuitars.CellValidated               += UpdateData;
            DataGridGuitars.SelectionChanged            += UpdateData;

            DataGridDecscriptGuitars.DataSource         = context.TableDescriptionGuitars;
            DataGridDecscriptGuitars.RowEnter           += DataGrid_RowEnter;
            DataGridDecscriptGuitars.CellValidated      += UpdateData;
            DataGridDecscriptGuitars.SelectionChanged   += UpdateData;


            DataGridManufactInfo.DataSource             = context.TableManufacturerInfoes;
            DataGridManufactInfo.RowEnter               += DataGrid_RowEnter;
            DataGridManufactInfo.CellValidated          += UpdateData;
            DataGridManufactInfo.SelectionChanged       += UpdateData;


            DataGridContacts.DataSource                 = context.TableContacts;
            DataGridContacts.RowEnter                   += DataGrid_RowEnter;
            DataGridContacts.CellValidated              += UpdateData;
            DataGridContacts.SelectionChanged           += UpdateData;

            DataGridAddress.DataSource                  = context.TableAdresses;
            DataGridAddress.RowEnter                    += DataGrid_RowEnter;
            DataGridAddress.CellValidated               += UpdateData;
            DataGridAddress.SelectionChanged            += UpdateData;

            DataGridPhones.DataSource                   = context.TablePhoneNumbers;
            DataGridPhones.RowEnter                     += DataGrid_RowEnter;
            DataGridPhones.CellValidated                += UpdateData;
            DataGridPhones.SelectionChanged             += UpdateData;

            DataGridGuitarsColoring.DataSource          = context.TableColorSetsGuitars;
            DataGridGuitarsColoring.RowEnter            += DataGrid_RowEnter;
            DataGridGuitarsColoring.CellValidated       += UpdateData;
            DataGridGuitarsColoring.SelectionChanged    += UpdateData;

            DataGridColorSchemes.DataSource             = context.TableExGuitarColors;
            DataGridColorSchemes.RowEnter               += DataGrid_RowEnter;
            DataGridColorSchemes.CellValidated          += UpdateData;
            DataGridColorSchemes.SelectionChanged       += UpdateData;

            DeleteButton.Visible = false;
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            ImageCollection = new Dictionary<string,Image>();
            ImageCollection.Add("LoginActive", Image.FromFile(Path + "LoginGreen.jpg", false));
            ImageCollection.Add("LoginNotActive", Image.FromFile(Path + "LoginGrey.jpg", false));

        }
        
        private void DeleteButton_Click(object sender, EventArgs e)
        {

            try
            {

                IsUpdated = false;
                if (CurrentDataGrid == null)
                    return;
                foreach (DataGridViewRow index in CurrentDataGrid.SelectedRows)
                {

                    if (TableBox.SelectedIndex == 5)
                        context.Delete<string>(TableBox.SelectedIndex, (string)index.Cells[0].Value);
                    else
                       context.Delete<int>(TableBox.SelectedIndex, Convert.ToInt32(index.Cells[0].Value));
                    
                }
                CurrentDataGrid.ClearSelection();
                context.SaveChanges();
                IsUpdated = true;
                
            }
            catch (DbEntityValidationException ex)
            {
                ReCreateContext();
                MessageBox.Show("Invalid data format.",
                          "Warning",
                          MessageBoxButtons.OK,
                          MessageBoxIcon.Warning);
            }
            catch (ObjectDisposedException ex)
            {
                ReCreateContext();
                MessageBox.Show("There is no connection to the database.",
                          "Warning",
                          MessageBoxButtons.OK,
                          MessageBoxIcon.Warning);
            }
            catch
            {
                ReCreateContext();
                MessageBox.Show("Access denied or an error occurred sending updates to the database.",
                          "Warning",
                          MessageBoxButtons.OK,
                          MessageBoxIcon.Warning);
            }
          
           
        }

        private void DataGrid_RowEnter(object sender, DataGridViewCellEventArgs e)
        {

            if (e.RowIndex != 0)
            {
                CurrentDataGrid = ((DataGridView)sender);
               
                DeleteButton.Visible = true;   
            }
            

        }

        private void UpdateData(object sender, EventArgs e)
        {
            try
            {
                if (IsUpdated)
                {
                    context.SaveChanges();
                    ((DataGridView)sender).Invalidate();
                }
            }
            catch (DbEntityValidationException ex)
            {
                ReCreateContext();
                MessageBox.Show("Invalid data format.",
                          "Warning",
                          MessageBoxButtons.OK,
                          MessageBoxIcon.Warning);
            }
            catch (ObjectDisposedException ex)
            {
                ReCreateContext();
                MessageBox.Show("There is no connection to the database.",
                          "Warning",
                          MessageBoxButtons.OK,
                          MessageBoxIcon.Warning);
            }
            catch
            {
                ReCreateContext();
                MessageBox.Show("Access denied or an error occurred sending updates to the database.",
                          "Warning",
                          MessageBoxButtons.OK,
                          MessageBoxIcon.Warning);
            }
        }
       private void  ReCreateContext()
       {
           if (context != null)
           {
               IsUpdated = false;
               ResetDataBinding();
               string Login = context.Login;
               string Password = context.Password;
               if (Login == null)
               {
                   context = new DBOperation();
               }
               else
               {
                   context = new DBOperation(Login, Password);
               }
               DataBinding();
               IsUpdated = true;
           }

       }
       private void LogInButton_Click(object sender, EventArgs e)
        {
            if (context == null)
            {
                LogInDialog = new AuthorizationForm();
                LogInDialog.AuthorizationSqlServerEvent += LogInSqlserver;
                LogInDialog.AuthorizationWindowsEvent += LogInWindows;
                LogInDialog.ShowDialog();
                
            }
        }
        private bool LogInSqlserver(string User, string Pwd)
        {
            try
            {
                context = new DBOperation(User, Pwd);
                DataBinding();
                LogInButton.Image = ImageCollection["LoginNotActive"];
                RestoreButton.Visible = false;
            }
            catch
            {
                return false;
            }
            return true;
        }
        private bool LogInWindows()
        {
            try
            {
                context = new DBOperation();
                DataBinding();
                LogInButton.Image = ImageCollection["LoginNotActive"];
                RestoreButton.Visible = false;
            }
            catch
            {
                context = null;
                return false;
            }
            return true;
        }
        private void LogOutButton_Click(object sender, EventArgs e)
        {
            ResetDataBinding();
            LogInButton.Image = ImageCollection["LoginActive"];
            LogInButton.Invalidate();
            context = null;
            RestoreButton.Visible = true;
        }

     
        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void RestoreButton_Click(object sender, EventArgs e)
        {
            using (SqlConnection cn = new SqlConnection())
            {
                try
                {
                    cn.ConnectionString = @"Data Source=(local)\SQLEXPRESS;Integrated Security=SSPI;Initial Catalog=master";
                    cn.Open();
                    string strSQL = @"RESTORE DATABASE [Database guitars] FROM DISK = '\DbBackup'";
                    SqlCommand myCommand = new SqlCommand(strSQL, cn);
                    int res = myCommand.ExecuteNonQuery();
                    MessageBox.Show("The database was restored from a backup!",
                                    "Information",
                                    MessageBoxButtons.OK,
                                    MessageBoxIcon.Information);
                }
                catch(Exception ex)
                {
                    MessageBox.Show(ex.Message,
                                    "Warning",
                                    MessageBoxButtons.OK,
                                    MessageBoxIcon.Warning);
                }
            }
            // context.Database.ExecuteSqlCommand(@"RESTORE DATABASE [Database guitars] FROM DISK = '\DbBackup'");
        }

        private void BackupButton_Click(object sender, EventArgs e)
        {
            try
            {
                System.Data.SqlClient.SqlParameter param = new System.Data.SqlClient.SqlParameter();
                var ret = context.Database.SqlQuery<int>("CreateBackup ", param);
                MessageBox.Show("Was created a backup copy of the database!",
                                "Information",
                                MessageBoxButtons.OK,
                                MessageBoxIcon.Information);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message,
                                "Warning",
                                MessageBoxButtons.OK,
                                MessageBoxIcon.Warning);

            }
           
        }

        private void toolStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {

        }

        private void DataGridDecscriptGuitars_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void Refresh_Click(object sender, EventArgs e)
        {
            try
            {
                ReCreateContext();
            }
            catch 
            {
                MessageBox.Show("There is no connection to the database.",
                          "Warning",
                          MessageBoxButtons.OK,
                          MessageBoxIcon.Warning);
            }
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            About win = new About();
            win.ShowDialog();

        }

    }
}
