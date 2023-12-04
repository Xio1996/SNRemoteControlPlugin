namespace RemoteControlClient
{
    partial class frmRCClient
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            txtFilePath = new TextBox();
            lblFilepath = new Label();
            btnFilePath = new Button();
            ofdFilePathINI = new OpenFileDialog();
            groupBox1 = new GroupBox();
            txtOutFilePath = new TextBox();
            label2 = new Label();
            btnRepopulate = new Button();
            txtCmdFilePath = new TextBox();
            label1 = new Label();
            groupBox2 = new GroupBox();
            txtCmd = new TextBox();
            label9 = new Label();
            txtFOV = new TextBox();
            label8 = new Label();
            txtDecAlt = new TextBox();
            label7 = new Label();
            txtRAAz = new TextBox();
            label6 = new Label();
            txtID = new TextBox();
            cbCmd = new ComboBox();
            label5 = new Label();
            label4 = new Label();
            label3 = new Label();
            button1 = new Button();
            comboBox1 = new ComboBox();
            groupBox3 = new GroupBox();
            cbGetCommands = new ComboBox();
            btnGet = new Button();
            txtGetInfo = new TextBox();
            fileSystemWatcher1 = new FileSystemWatcher();
            groupBox1.SuspendLayout();
            groupBox2.SuspendLayout();
            groupBox3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)fileSystemWatcher1).BeginInit();
            SuspendLayout();
            // 
            // txtFilePath
            // 
            txtFilePath.Location = new Point(12, 32);
            txtFilePath.Name = "txtFilePath";
            txtFilePath.Size = new Size(432, 23);
            txtFilePath.TabIndex = 0;
            // 
            // lblFilepath
            // 
            lblFilepath.AutoSize = true;
            lblFilepath.Location = new Point(13, 10);
            lblFilepath.Name = "lblFilepath";
            lblFilepath.Size = new Size(229, 15);
            lblFilepath.TabIndex = 1;
            lblFilepath.Text = "File Path to 'RemoteControl_Win32.ini' file";
            // 
            // btnFilePath
            // 
            btnFilePath.Location = new Point(450, 32);
            btnFilePath.Name = "btnFilePath";
            btnFilePath.Size = new Size(36, 23);
            btnFilePath.TabIndex = 2;
            btnFilePath.Text = "...";
            btnFilePath.UseVisualStyleBackColor = true;
            btnFilePath.Click += btnFilePath_Click;
            // 
            // groupBox1
            // 
            groupBox1.Controls.Add(txtOutFilePath);
            groupBox1.Controls.Add(label2);
            groupBox1.Controls.Add(btnRepopulate);
            groupBox1.Controls.Add(txtCmdFilePath);
            groupBox1.Controls.Add(label1);
            groupBox1.Location = new Point(13, 66);
            groupBox1.Name = "groupBox1";
            groupBox1.Size = new Size(473, 144);
            groupBox1.TabIndex = 3;
            groupBox1.TabStop = false;
            groupBox1.Text = "RemoteControl_Win32.ini";
            // 
            // txtOutFilePath
            // 
            txtOutFilePath.Location = new Point(8, 82);
            txtOutFilePath.Name = "txtOutFilePath";
            txtOutFilePath.ReadOnly = true;
            txtOutFilePath.Size = new Size(457, 23);
            txtOutFilePath.TabIndex = 6;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(8, 64);
            label2.Name = "label2";
            label2.Size = new Size(75, 15);
            label2.TabIndex = 5;
            label2.Text = "Out File Path";
            // 
            // btnRepopulate
            // 
            btnRepopulate.Location = new Point(383, 114);
            btnRepopulate.Name = "btnRepopulate";
            btnRepopulate.Size = new Size(84, 23);
            btnRepopulate.TabIndex = 4;
            btnRepopulate.Text = "Repopulate";
            btnRepopulate.UseVisualStyleBackColor = true;
            btnRepopulate.Click += btnRepopulate_Click;
            // 
            // txtCmdFilePath
            // 
            txtCmdFilePath.Location = new Point(10, 37);
            txtCmdFilePath.Name = "txtCmdFilePath";
            txtCmdFilePath.ReadOnly = true;
            txtCmdFilePath.Size = new Size(457, 23);
            txtCmdFilePath.TabIndex = 2;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(10, 19);
            label1.Name = "label1";
            label1.Size = new Size(81, 15);
            label1.TabIndex = 0;
            label1.Text = "Cmd File Path";
            // 
            // groupBox2
            // 
            groupBox2.Controls.Add(txtCmd);
            groupBox2.Controls.Add(label9);
            groupBox2.Controls.Add(txtFOV);
            groupBox2.Controls.Add(label8);
            groupBox2.Controls.Add(txtDecAlt);
            groupBox2.Controls.Add(label7);
            groupBox2.Controls.Add(txtRAAz);
            groupBox2.Controls.Add(label6);
            groupBox2.Controls.Add(txtID);
            groupBox2.Controls.Add(cbCmd);
            groupBox2.Controls.Add(label5);
            groupBox2.Controls.Add(label4);
            groupBox2.Controls.Add(label3);
            groupBox2.Controls.Add(button1);
            groupBox2.Controls.Add(comboBox1);
            groupBox2.Location = new Point(12, 220);
            groupBox2.Name = "groupBox2";
            groupBox2.Size = new Size(474, 213);
            groupBox2.TabIndex = 4;
            groupBox2.TabStop = false;
            groupBox2.Text = "Example Remote Control Commands";
            // 
            // txtCmd
            // 
            txtCmd.Location = new Point(9, 184);
            txtCmd.Name = "txtCmd";
            txtCmd.ReadOnly = true;
            txtCmd.Size = new Size(352, 23);
            txtCmd.TabIndex = 17;
            // 
            // label9
            // 
            label9.AutoSize = true;
            label9.Location = new Point(344, 91);
            label9.Name = "label9";
            label9.Size = new Size(60, 15);
            label9.TabIndex = 16;
            label9.Text = "FOV (deg)";
            // 
            // txtFOV
            // 
            txtFOV.Enabled = false;
            txtFOV.Location = new Point(344, 109);
            txtFOV.Name = "txtFOV";
            txtFOV.Size = new Size(120, 23);
            txtFOV.TabIndex = 15;
            // 
            // label8
            // 
            label8.AutoSize = true;
            label8.Location = new Point(286, 136);
            label8.Name = "label8";
            label8.Size = new Size(90, 15);
            label8.TabIndex = 14;
            label8.Text = "Dec or Alt (deg)";
            // 
            // txtDecAlt
            // 
            txtDecAlt.Enabled = false;
            txtDecAlt.Location = new Point(286, 154);
            txtDecAlt.Name = "txtDecAlt";
            txtDecAlt.Size = new Size(175, 23);
            txtDecAlt.TabIndex = 13;
            // 
            // label7
            // 
            label7.AutoSize = true;
            label7.Location = new Point(98, 136);
            label7.Name = "label7";
            label7.Size = new Size(172, 15);
            label7.TabIndex = 12;
            label7.Text = "RA (Decimal Hours) or Az (deg)";
            // 
            // txtRAAz
            // 
            txtRAAz.Enabled = false;
            txtRAAz.Location = new Point(98, 154);
            txtRAAz.Name = "txtRAAz";
            txtRAAz.Size = new Size(175, 23);
            txtRAAz.TabIndex = 11;
            // 
            // label6
            // 
            label6.AutoSize = true;
            label6.Location = new Point(98, 91);
            label6.Name = "label6";
            label6.Size = new Size(52, 15);
            label6.TabIndex = 10;
            label6.Text = "ID (M33)";
            // 
            // txtID
            // 
            txtID.Enabled = false;
            txtID.Location = new Point(98, 109);
            txtID.Name = "txtID";
            txtID.Size = new Size(240, 23);
            txtID.TabIndex = 9;
            // 
            // cbCmd
            // 
            cbCmd.DropDownStyle = ComboBoxStyle.DropDownList;
            cbCmd.FormattingEnabled = true;
            cbCmd.Items.AddRange(new object[] { "target", "altaz", "fov" });
            cbCmd.Location = new Point(8, 109);
            cbCmd.MaxDropDownItems = 3;
            cbCmd.Name = "cbCmd";
            cbCmd.Size = new Size(84, 23);
            cbCmd.TabIndex = 8;
            cbCmd.SelectedIndexChanged += cbCmd_SelectedIndexChanged;
            // 
            // label5
            // 
            label5.AutoSize = true;
            label5.Location = new Point(8, 91);
            label5.Name = "label5";
            label5.Size = new Size(64, 15);
            label5.TabIndex = 7;
            label5.Text = "Command";
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Location = new Point(8, 36);
            label4.Name = "label4";
            label4.Size = new Size(241, 15);
            label4.TabIndex = 6;
            label4.Text = "create your own command and press 'Send'.";
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(8, 19);
            label3.Name = "label3";
            label3.Size = new Size(394, 15);
            label3.TabIndex = 5;
            label3.Text = "Select an example SN Remote Control command from the drop-down or ";
            // 
            // button1
            // 
            button1.Location = new Point(377, 183);
            button1.Name = "button1";
            button1.Size = new Size(84, 23);
            button1.TabIndex = 3;
            button1.Text = "Do";
            button1.UseVisualStyleBackColor = true;
            button1.Click += button1_Click;
            // 
            // comboBox1
            // 
            comboBox1.DropDownStyle = ComboBoxStyle.DropDownList;
            comboBox1.FormattingEnabled = true;
            comboBox1.Items.AddRange(new object[] { "Target Polaris 10 deg fov", "Target M13 5 deg fov", "Target NGC6569 1.1 deg fov", "AltAz 45 deg, 180 deg, 107 deg fov", "AltAz 0 deg, 90 deg, 45 deg fov", "FOV 10 deg", "FOV 110 deg" });
            comboBox1.Location = new Point(8, 62);
            comboBox1.Name = "comboBox1";
            comboBox1.Size = new Size(370, 23);
            comboBox1.TabIndex = 0;
            comboBox1.SelectedIndexChanged += comboBox1_SelectedIndexChanged;
            // 
            // groupBox3
            // 
            groupBox3.Controls.Add(cbGetCommands);
            groupBox3.Controls.Add(btnGet);
            groupBox3.Controls.Add(txtGetInfo);
            groupBox3.Location = new Point(13, 444);
            groupBox3.Name = "groupBox3";
            groupBox3.Size = new Size(473, 129);
            groupBox3.TabIndex = 5;
            groupBox3.TabStop = false;
            groupBox3.Text = "Get Commands";
            // 
            // cbGetCommands
            // 
            cbGetCommands.DropDownStyle = ComboBoxStyle.DropDownList;
            cbGetCommands.FormattingEnabled = true;
            cbGetCommands.Items.AddRange(new object[] { "Get Selected Object Details", "Get Viewer Location", "Get FOV", "Get View Centre Position", "Get Current Time (Julian)" });
            cbGetCommands.Location = new Point(8, 23);
            cbGetCommands.Name = "cbGetCommands";
            cbGetCommands.Size = new Size(367, 23);
            cbGetCommands.TabIndex = 5;
            // 
            // btnGet
            // 
            btnGet.Location = new Point(379, 22);
            btnGet.Name = "btnGet";
            btnGet.Size = new Size(84, 23);
            btnGet.TabIndex = 4;
            btnGet.Text = "Get";
            btnGet.UseVisualStyleBackColor = true;
            btnGet.Click += btnGet_Click;
            // 
            // txtGetInfo
            // 
            txtGetInfo.Location = new Point(10, 51);
            txtGetInfo.Multiline = true;
            txtGetInfo.Name = "txtGetInfo";
            txtGetInfo.ReadOnly = true;
            txtGetInfo.Size = new Size(457, 72);
            txtGetInfo.TabIndex = 2;
            // 
            // fileSystemWatcher1
            // 
            fileSystemWatcher1.EnableRaisingEvents = true;
            fileSystemWatcher1.NotifyFilter = NotifyFilters.CreationTime;
            fileSystemWatcher1.SynchronizingObject = this;
            // 
            // frmRCClient
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(498, 581);
            Controls.Add(groupBox3);
            Controls.Add(groupBox2);
            Controls.Add(groupBox1);
            Controls.Add(btnFilePath);
            Controls.Add(lblFilepath);
            Controls.Add(txtFilePath);
            FormBorderStyle = FormBorderStyle.FixedSingle;
            Name = "frmRCClient";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "Remote Control Plugin Client for SN";
            groupBox1.ResumeLayout(false);
            groupBox1.PerformLayout();
            groupBox2.ResumeLayout(false);
            groupBox2.PerformLayout();
            groupBox3.ResumeLayout(false);
            groupBox3.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)fileSystemWatcher1).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion
        private TextBox txtFilePath;
        private Label lblFilepath;
        private Button btnFilePath;
        private OpenFileDialog ofdFilePathINI;
        private GroupBox groupBox1;
        private TextBox txtCmdFilePath;
        private Label label1;
        private GroupBox groupBox2;
        private Button button1;
        private ComboBox comboBox1;
        private Button btnRepopulate;
        private Label label3;
        private Label label5;
        private Label label4;
        private ComboBox cbCmd;
        private Label label8;
        private TextBox txtDecAlt;
        private Label label7;
        private TextBox txtRAAz;
        private Label label6;
        private TextBox txtID;
        private Label label9;
        private TextBox txtFOV;
        private TextBox txtCmd;
        private GroupBox groupBox3;
        private ComboBox cbGetCommands;
        private Button btnGet;
        private TextBox txtGetInfo;
        private TextBox txtOutFilePath;
        private Label label2;
        private FileSystemWatcher fileSystemWatcher1;
    }
}