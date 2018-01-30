namespace ClientDBEditor
{
    partial class AuthorizationForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.LoginTextBox = new System.Windows.Forms.TextBox();
            this.LoginLabel = new System.Windows.Forms.Label();
            this.PWDTextBox = new System.Windows.Forms.MaskedTextBox();
            this.PWDLabel = new System.Windows.Forms.Label();
            this.Cancel = new System.Windows.Forms.Button();
            this.Connection = new System.Windows.Forms.Button();
            this.AuthenticationComboBox = new System.Windows.Forms.ComboBox();
            this.splitter1 = new System.Windows.Forms.Splitter();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // LoginTextBox
            // 
            this.LoginTextBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.LoginTextBox.Location = new System.Drawing.Point(297, 197);
            this.LoginTextBox.Name = "LoginTextBox";
            this.LoginTextBox.ReadOnly = true;
            this.LoginTextBox.Size = new System.Drawing.Size(301, 23);
            this.LoginTextBox.TabIndex = 0;
            // 
            // LoginLabel
            // 
            this.LoginLabel.AutoSize = true;
            this.LoginLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.LoginLabel.Location = new System.Drawing.Point(244, 200);
            this.LoginLabel.Name = "LoginLabel";
            this.LoginLabel.Size = new System.Drawing.Size(47, 17);
            this.LoginLabel.TabIndex = 1;
            this.LoginLabel.Text = "Login:";
            // 
            // PWDTextBox
            // 
            this.PWDTextBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.PWDTextBox.Location = new System.Drawing.Point(297, 240);
            this.PWDTextBox.Name = "PWDTextBox";
            this.PWDTextBox.PromptChar = '*';
            this.PWDTextBox.ReadOnly = true;
            this.PWDTextBox.Size = new System.Drawing.Size(301, 23);
            this.PWDTextBox.TabIndex = 3;
            this.PWDTextBox.UseSystemPasswordChar = true;
            // 
            // PWDLabel
            // 
            this.PWDLabel.AutoSize = true;
            this.PWDLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.PWDLabel.Location = new System.Drawing.Point(218, 243);
            this.PWDLabel.Name = "PWDLabel";
            this.PWDLabel.Size = new System.Drawing.Size(73, 17);
            this.PWDLabel.TabIndex = 4;
            this.PWDLabel.Text = "Password:";
            // 
            // Cancel
            // 
            this.Cancel.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Cancel.Location = new System.Drawing.Point(487, 283);
            this.Cancel.Name = "Cancel";
            this.Cancel.Size = new System.Drawing.Size(90, 34);
            this.Cancel.TabIndex = 6;
            this.Cancel.Text = "Cancel";
            this.Cancel.UseVisualStyleBackColor = true;
            this.Cancel.Click += new System.EventHandler(this.Cancel_Click);
            // 
            // Connection
            // 
            this.Connection.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.25F);
            this.Connection.Location = new System.Drawing.Point(297, 283);
            this.Connection.Name = "Connection";
            this.Connection.Size = new System.Drawing.Size(90, 34);
            this.Connection.TabIndex = 7;
            this.Connection.Text = "Connection";
            this.Connection.UseVisualStyleBackColor = true;
            this.Connection.Click += new System.EventHandler(this.Connection_Click);
            // 
            // AuthenticationComboBox
            // 
            this.AuthenticationComboBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.25F);
            this.AuthenticationComboBox.FormattingEnabled = true;
            this.AuthenticationComboBox.Items.AddRange(new object[] {
            "Windows Authentication",
            "SQL Server Authentication"});
            this.AuthenticationComboBox.Location = new System.Drawing.Point(297, 159);
            this.AuthenticationComboBox.MaxDropDownItems = 2;
            this.AuthenticationComboBox.Name = "AuthenticationComboBox";
            this.AuthenticationComboBox.Size = new System.Drawing.Size(301, 25);
            this.AuthenticationComboBox.TabIndex = 8;
            this.AuthenticationComboBox.SelectedIndexChanged += new System.EventHandler(this.AuthenticationComboBox_SelectedIndexChanged);
            // 
            // splitter1
            // 
            this.splitter1.Location = new System.Drawing.Point(0, 0);
            this.splitter1.Name = "splitter1";
            this.splitter1.Size = new System.Drawing.Size(3, 359);
            this.splitter1.TabIndex = 10;
            this.splitter1.TabStop = false;
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = global::ClientDBEditor.Properties.Resources.User;
            this.pictureBox1.Location = new System.Drawing.Point(384, 28);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(120, 125);
            this.pictureBox1.TabIndex = 9;
            this.pictureBox1.TabStop = false;
            // 
            // AuthorizationForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(914, 359);
            this.Controls.Add(this.splitter1);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.AuthenticationComboBox);
            this.Controls.Add(this.Connection);
            this.Controls.Add(this.Cancel);
            this.Controls.Add(this.PWDLabel);
            this.Controls.Add(this.PWDTextBox);
            this.Controls.Add(this.LoginLabel);
            this.Controls.Add(this.LoginTextBox);
            this.Name = "AuthorizationForm";
            this.Text = "Авторизация";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox LoginTextBox;
        private System.Windows.Forms.Label LoginLabel;
        private System.Windows.Forms.MaskedTextBox PWDTextBox;
        private System.Windows.Forms.Label PWDLabel;
        private System.Windows.Forms.Button Cancel;
        private System.Windows.Forms.Button Connection;
        private System.Windows.Forms.ComboBox AuthenticationComboBox;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Splitter splitter1;
    }
}