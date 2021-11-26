using Lab_04_NoProxy.SimplexRef;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lab_04_NoProxy
{
    public partial class Form1 : Form
    {
        private Dictionary<string, bool> is_ok = new Dictionary<string, bool>();
        private SimplexSoapClient client = new SimplexSoapClient();
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            this.client.Open();
        }

        protected override void OnClosing(CancelEventArgs e)
        {
            this.client.Close();
            base.OnClosing(e);
        }

        private async void Send_Click(object sender, EventArgs e)
        {
            Error_Label.Hide();
            if (is_ok.Count != 0 && is_ok.All(x=>x.Value))
            {
                SimplexRef.A a1 = new SimplexRef.A
                {
                    S = A1_S.Text,
                    K = int.Parse(A1_K.Text),
                    F = float.Parse(A1_F.Text)
                },
                a2 = new SimplexRef.A
                {
                    S = A2_S.Text,
                    K = int.Parse(A2_K.Text),
                    F = float.Parse(A2_F.Text)
                };

                try {
                    SumResponse response = await client.SumAsync(a1, a2);
                    Result_S.Text = response.Body.SumResult.S;
                    Result_K.Text = response.Body.SumResult.K.ToString();
                    Result_F.Text = response.Body.SumResult.F.ToString();
                } catch (Exception) { 
                    Error_Label.Show();
                }
                
            }
        }

        private void A2_K_TextChanged(object sender, EventArgs e)
        {
            if (!int.TryParse(A2_K.Text, out int a2_k))
            {
                SetOrInsert(A2_K.Name, false);
                A2_K_Err.Visible = true;
            } else
            {
                SetOrInsert(A2_K.Name, true);
                A2_K_Err.Visible = false;
            }
        }

        private void A2_F_TextChanged(object sender, EventArgs e)
        {
            if (!float.TryParse(A2_F.Text, out float a2_f))
            {
                SetOrInsert(A2_F.Name, false);
                A2_F_Err.Visible = true;
            }
            else
            {
                SetOrInsert(A2_F.Name, true);
                A2_F_Err.Visible = false;
            }
        }

        private void A1_F_TextChanged(object sender, EventArgs e)
        {
            if (!float.TryParse(A1_F.Text, out float a1_f))
            {
                SetOrInsert(A1_F.Name, false);
                A1_F_Err.Visible = true;
            }
            else
            {
                SetOrInsert(A1_F.Name, true);
                A1_F_Err.Visible = false;
            }
        }

        private void A1_K_TextChanged(object sender, EventArgs e)
        {
            if (!int.TryParse(A1_K.Text, out int a1_k))
            {
                SetOrInsert(A1_K.Name, false);
                A1_K_Err.Visible = true;
            }
            else
            {
                SetOrInsert(A1_K.Name, true);
                A1_K_Err.Visible = false;
            }
        }

        private void SetOrInsert(string key, bool value)
        {
            if (!is_ok.ContainsKey(key))
                is_ok.Add(key, value);
            else
                is_ok[key] = value;
        }

        private void clear_Click(object sender, EventArgs e)
        {
            A1_S.Clear(); A2_S.Clear(); Result_S.Clear();
            A1_K.Clear(); A2_K.Clear(); Result_K.Clear();
            A1_F.Clear(); A2_F.Clear(); Result_F.Clear();
            A1_K_Err.Hide(); A2_K_Err.Hide();
            A1_F_Err.Hide(); A2_F_Err.Hide();
            Error_Label.Hide();
        }
    }
}
