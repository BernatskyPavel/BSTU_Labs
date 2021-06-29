using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net.Http;

namespace Handler_Client
{
    public partial class Form1 : Form
    {
        static readonly HttpClient client = new HttpClient();

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void btnSend_ClickAsync(object sender, EventArgs e)
        {
            lbStatus.Visible = false;
            if (!Uri.IsWellFormedUriString(tbURL.Text, UriKind.Absolute))
            {
                lbStatus.Text = "Invalid URL!";
                lbStatus.ForeColor = Color.Red;
                lbStatus.Visible = true;
                return;
            }

            string x = tbParmX.Text;
            double d_x;
            if (!double.TryParse(x, out d_x))
            {
                lbStatus.Text = "Parameter X Error!";
                lbStatus.ForeColor = Color.Red;
                lbStatus.Visible = true;
                return;
            }
            string y = tbParmY.Text;
            double d_y;
            double.TryParse(y, out d_y);
            if (!double.TryParse(y, out d_y))
            {
                lbStatus.Text = "Parameter Y Error!";
                lbStatus.ForeColor = Color.Red;
                lbStatus.Visible = true;
                return;
            }

            HttpRequestMessage request = new HttpRequestMessage(HttpMethod.Post, tbURL.Text);

            request.Content = new StringContent($@"{{""x"":""{d_x}"",""y"":""{d_y}""}}", Encoding.UTF8, "application/json");

            HttpResponseMessage response = client.SendAsync(request).Result;

            if (!response.IsSuccessStatusCode)
            {
                lbStatus.Text = $@"Request Error!";
                lbStatus.ForeColor = System.Drawing.Color.Red;
                lbStatus.Visible = true;
                return;
            }

            tbResult.Text = response.Content.ReadAsStringAsync().Result;
            lbStatus.Text = "Success!";
            lbStatus.ForeColor = Color.Green;
            lbStatus.Visible = true;
            return;
        }
    }
}
