namespace RemoteControlClient
{
    public partial class frmRCClient : Form
    {
        private string sConfigFilePath = "";
        private string sRCCmdFilePath = "";
        private string sRCOutFilePath = "";

        public frmRCClient()
        {
            InitializeComponent();

            sConfigFilePath = Properties.Settings.Default.ConfigFilePath;
            RePopulate();
        }

        private bool GetCmdFilePath(string sConfigFilePath)
        {
            try
            {
                sRCCmdFilePath = File.ReadAllText(sConfigFilePath);
                return true;
            }
            catch
            {
                return false;
            }
        }

        private void RePopulate()
        {
            if (GetCmdFilePath(sConfigFilePath))
            {
                txtFilePath.Text = sConfigFilePath;
                txtCmdFilePath.Text = sRCCmdFilePath;
                
                if (File.Exists(sRCCmdFilePath))
                {
                    File.Delete(sRCCmdFilePath);
                }

                sRCOutFilePath = sRCCmdFilePath.Substring(0, sRCCmdFilePath.LastIndexOf(@"\") + 1) + "snrcout.txt";
                txtOutFilePath.Text = sRCOutFilePath;

                if (File.Exists(sRCOutFilePath))
                { 
                    File.Delete (sRCOutFilePath);
                }

                Properties.Settings.Default.ConfigFilePath = sConfigFilePath;
                Properties.Settings.Default.Save();
            }
            else
            {
                txtFilePath.Text = "ERROR - RemoteControl_Win32.ini invalid content!";
            }
        }

        private void btnFilePath_Click(object sender, EventArgs e)
        {
            if (ofdFilePathINI.ShowDialog() == DialogResult.OK)
            {
                sConfigFilePath = ofdFilePathINI.FileName;
                RePopulate();
            }
        }

        private void cbCmd_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (cbCmd.SelectedIndex)
            {
                case 0:
                    txtID.Enabled = true;
                    txtRAAz.Enabled = true;
                    txtDecAlt.Enabled = true;
                    txtFOV.Enabled = true;
                    break;
                case 1:
                    txtID.Enabled = false;
                    txtRAAz.Enabled = true;
                    txtDecAlt.Enabled = true;
                    txtFOV.Enabled = true;
                    break;
                case 2:
                    txtID.Enabled = false;
                    txtRAAz.Enabled = false;
                    txtDecAlt.Enabled = false;
                    txtFOV.Enabled = true;
                    break;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string sCmd = "";

            if ( File.Exists(sRCCmdFilePath))
            {
                txtFilePath.Text = "WARNING - Starry Night still processing a command.";
                return;
            }

            switch (cbCmd.SelectedIndex)
            {
                case 0:
                    sCmd = "target|" + txtID.Text + "|" + txtRAAz.Text + "|" + txtDecAlt.Text + "|" + txtFOV.Text;
                    break;
                case 1:
                    sCmd = "altaz|" + txtDecAlt.Text + "|" + txtRAAz.Text + "|" + txtFOV.Text;
                    break;
                case 2:
                    sCmd = "fov|" + txtFOV.Text;
                    break;
            }

            if (sCmd.Length > 0)
            {
                txtCmd.Text = sCmd;
                File.WriteAllText(sRCCmdFilePath, sCmd);
            }
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (comboBox1.SelectedIndex)
            {
                case 0:
                    cbCmd.SelectedIndex = 0;
                    txtID.Text = "Polaris";
                    txtRAAz.Text = "2.530195";
                    txtDecAlt.Text = "89.26417";
                    txtFOV.Text = "10";
                    break;
                case 1:
                    cbCmd.SelectedIndex = 0;
                    txtID.Text = "M13";
                    txtRAAz.Text = "16.69478";
                    txtDecAlt.Text = "36.4598";
                    txtFOV.Text = "5";
                    break;
                case 2:
                    cbCmd.SelectedIndex = 0;
                    txtID.Text = "NGC6569";
                    txtRAAz.Text = "18.22744";
                    txtDecAlt.Text = "-31.8265";
                    txtFOV.Text = "1.1";
                    break;
                case 3:
                    cbCmd.SelectedIndex = 1;
                    txtRAAz.Text = "180";
                    txtDecAlt.Text = "45";
                    txtFOV.Text = "107";
                    break;
                case 4:
                    cbCmd.SelectedIndex = 1;
                    txtRAAz.Text = "90";
                    txtDecAlt.Text = "0";
                    txtFOV.Text = "45";
                    break;
                case 5:
                    cbCmd.SelectedIndex = 2;
                    txtFOV.Text = "10";
                    break;
                case 6:
                    cbCmd.SelectedIndex = 2;
                    txtFOV.Text = "110";
                    break;
            }
        }

        private void btnGet_Click(object sender, EventArgs e)
        {
            string sCmd = "";

            switch (cbGetCommands.SelectedIndex)
            {
                case 0:
                    sCmd = "getselobj";     // Get information on the selected object.
                    break;
                case 1:
                    sCmd = "getviewerloc";  // Get the view location.
                    break;
                case 2:
                    sCmd = "getfov";        // Get current FOV
                    break;
                case 3:
                    sCmd = "getcentrecoords"; // Get the centre coordinates in the SN window's orientation.
                    break;
                case 4:
                    sCmd = "gettime";       // Get the current time (Julian).
                    break;
            }

            if (sCmd.Length > 0)
            {
                txtCmd.Text = sCmd;
                File.WriteAllText(sRCCmdFilePath, sCmd);

                while (!File.Exists(sRCOutFilePath))
                {
                    Thread.Sleep(500);
                }

                txtGetInfo.Text = File.ReadAllText(sRCOutFilePath);
                File.Delete(sRCOutFilePath);
            }
        }

        private void btnRepopulate_Click(object sender, EventArgs e)
        {
            RePopulate();
        }
    }
}