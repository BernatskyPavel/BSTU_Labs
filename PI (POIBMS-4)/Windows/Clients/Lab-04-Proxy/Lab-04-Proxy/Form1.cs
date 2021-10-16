using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net.Sockets;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lab_04_Proxy {
    using BoolDict = Dictionary<string, bool>;

    public partial class Form1 : Form {
        private Dictionary<string, BoolDict> forms = new Dictionary<string, BoolDict>();
        private Simplex service_proxy = new Simplex();
        //private Dictionary<string, bool> is_ok = new Dictionary<string, bool>();

        public Form1()
        {
            InitializeComponent();
            service_proxy.AddCompleted += (s, e) => {
                if(e.Error != null) {
                    Add_Err.Text = e.Error.Message;
                    Add_Err.Show();
                }
                else if (!e.Cancelled) {
                    Add_Result.Text = e.Result.ToString();
                }
            };
            service_proxy.ConcatCompleted += (s, e) => {
                if (e.Error != null) {
                    Concat_Err.Text = e.Error.Message;
                    Concat_Err.Show();
                }
                else if (!e.Cancelled) {
                    Concat_Result.Text = e.Result;
                }
            };
            service_proxy.SumCompleted += (s, e) => {
                if (e.Error != null) {
                    Sum_Err.Text = e.Error.Message;
                    Sum_Err.Show();
                }
                else if(!e.Cancelled) {
                    Result_S.Text = e.Result.S;
                    Result_F.Text = e.Result.F.ToString();
                    Result_K.Text = e.Result.K.ToString();
                }
            };
        }

        private void Form1_Load(object sender, EventArgs e)
        {
        }

        protected override void OnClosed(EventArgs e)
        {
            this.service_proxy.Dispose();
            base.OnClosed(e);
        }

        private void Generic_TextChanged(object sender, EventArgs e)
        {

            Control control = sender as Control;
            if (null == control.Parent.Tag || null == control.Tag) return;

            Type type = Type.GetType(control.Tag.ToString());
            if (type == null) return;

            MethodInfo method = type.GetMethod("TryParse", new Type[] { typeof(string), type.MakeByRefType() });
            if (method == null) return;

            object __ = Activator.CreateInstance(type);
            string tag = control.Parent.Tag as string;
            
            if (!forms.ContainsKey(tag)) {
                forms.Add(tag, new BoolDict());
            }

            bool result = (bool)method.Invoke(null, new object[] { control.Text, __ });
            SetOrInsert(forms[tag], control.Name, result);
            GetNextControl(control, true).Visible = !result;
        }

        private void SetOrInsert(BoolDict dict, string key, bool value)
        {
            if (!dict.ContainsKey(key)) {
                dict.Add(key, value);
            }
            else {
                dict[key] = value;
            }
        }

        private void Add_Btn_Click(object sender, EventArgs e)
        {
            Add_Err.Hide();
            Button sender_btn = sender as Button;
            if (sender_btn.Tag == null) {
                return;
            }

            string tag = sender_btn.Tag.ToString();
            if (forms.ContainsKey(tag) && forms[tag].Count != 0 && forms[tag].All(x => x.Value)) {
                this.service_proxy.AddAsync(int.Parse(Int1_tb.Text), int.Parse(Int2_tb.Text));
            }
        }

        private void Concat_Click(object sender, EventArgs e)
        {
            Button sender_btn = sender as Button;
            if (sender_btn.Tag == null) {
                return;
            }

            string tag = sender_btn.Tag.ToString();
            if (forms.ContainsKey(tag) && forms[tag].Count != 0 && forms[tag].All(x => x.Value)) {
                this.service_proxy.ConcatAsync(String_tb.Text, double.Parse(Double_tb.Text));
            }
        }

        private void Control_VisibleChanged(object sender, EventArgs e)
        {
            Control control = sender as Control;
            if (control.Tag != null) {
                if (!forms.ContainsKey(control.Tag.ToString())) {
                    forms.Add(control.Tag.ToString(), new BoolDict());
                }
                SetOrInsert(forms[control.Tag.ToString()], control.Name, false);
            }
        }

        private void Sum_Btn_Click(object sender, EventArgs e)
        {
            Button sender_btn = sender as Button;
            if (sender_btn.Tag == null) {
                return;
            }

            string tag = sender_btn.Tag.ToString();
            if (forms.ContainsKey(tag) && forms[tag].Count != 0 && forms[tag].All(x => x.Value)) {
                this.service_proxy.SumAsync(new A {
                    S = A1_S.Text,
                    K = int.Parse(A1_K.Text),
                    F = float.Parse(A1_F.Text)
                }, new A {
                    S = A2_S.Text,
                    K = int.Parse(A2_K.Text),
                    F = float.Parse(A2_F.Text)
                });
            }
        }

        private void clear_1_Click(object sender, EventArgs e)
        {
            Int1_tb.Clear(); Int1_Err.Hide();
            Int2_tb.Clear(); Int2_Err.Hide();
            Add_Result.Clear();
            Add_Err.Hide();
        }

        private void clear_2_Click(object sender, EventArgs e)
        {
            String_tb.Clear();
            Double_tb.Clear(); Double_Err.Hide();
            Concat_Result.Clear();
            Concat_Err.Hide();
        }

        private void clear_3_Click(object sender, EventArgs e)
        {
            A1_S.Clear();
            A1_K.Clear(); A1_K_Err.Hide();
            A1_F.Clear(); A1_F_Err.Hide();
            A2_S.Clear();
            A2_K.Clear(); A2_K_Err.Hide();
            A2_F.Clear(); A2_F_Err.Hide();
            Result_S.Clear();
            Result_K.Clear();
            Result_F.Clear();
            Sum_Err.Hide();
        }

    }
}
