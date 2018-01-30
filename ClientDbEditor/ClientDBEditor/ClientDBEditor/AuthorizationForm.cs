using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ClientDBEditor
{
    public partial class AuthorizationForm : Form
    {
        public delegate bool AuthorizationSqlServer(string User,string Pwd);
        public delegate bool AuthorizationWindows();
        public event AuthorizationSqlServer AuthorizationSqlServerEvent;
        public event AuthorizationWindows AuthorizationWindowsEvent;
        public AuthorizationForm()
        {
            InitializeComponent();
        }
       
        private void AuthenticationComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (AuthenticationComboBox.SelectedIndex == 0)
            {
                LoginTextBox.Clear();
                LoginTextBox.ReadOnly = true;
                PWDTextBox.Clear();
                PWDTextBox.ReadOnly = true;
            }
            else
            {
                LoginTextBox.ReadOnly = false;
                PWDTextBox.ReadOnly = false;
            }

        }

        private void Connection_Click(object sender, EventArgs e)
        {
            if (AuthenticationComboBox.SelectedIndex == 0)
            {
                if (AuthorizationWindowsEvent())
                {
                    Close();
                }
                else
                {
                    MessageBox.Show("Maybe your profile is not registered in the database.Contact your system administrator."
                                    , "Authorization error",
                                    MessageBoxButtons.OK,
                                    MessageBoxIcon.Warning);
                }
            }
            else
            {
                if (AuthorizationSqlServerEvent(LoginTextBox.Text, PWDTextBox.Text))
                {
                    Close();
                }
                else 
                {
                    MessageBox.Show("Unable to log in.May entered the username or password is not correct."
                                    , "Authorization error",
                                    MessageBoxButtons.OK,
                                    MessageBoxIcon.Warning);
                }
            }
        }

        private void Cancel_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
