using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using WebClients.Services.Lab_04;

namespace WebClients.LabViews {
    public partial class Lab_04 : System.Web.UI.Page {

        private static Simplex service = new Simplex();

        protected void Page_Load(object sender, EventArgs e)
        {

        }
        protected void add_btn_Click(object sender, EventArgs e)
        {
            if (int.TryParse(add_1.Text, out _) && int.TryParse(add_2.Text, out _)) {
                add_r.Text = service.Add(int.Parse(add_1.Text), int.Parse(add_2.Text)).ToString();
            }
        }

        protected void concat_btn_Click(object sender, EventArgs e)
        {
            if (double.TryParse(concat_2.Text, out _)) {
                concat_r.Text = service.Concat(concat_1.Text, double.Parse(concat_2.Text));
            }
        }

        protected void sum_btn_Click(object sender, EventArgs e)
        {
            if (int.TryParse(a1_k.Text, out _) && int.TryParse(a2_k.Text, out _)) {
                if (float.TryParse(a1_f.Text, out _) && float.TryParse(a2_f.Text, out _)) {
                    A result = service.Sum(
                        new A {
                            S = a1_S.Text,
                            K = int.Parse(a1_k.Text),
                            F = float.Parse(a1_f.Text),
                        },
                        new A {
                            S = a2_s.Text,
                            K = int.Parse(a2_k.Text),
                            F = float.Parse(a2_f.Text),
                        }
                    );
                    result_s.Text = result.S;
                    result_k.Text = result.K.ToString();
                    result_f.Text = result.F.ToString();
                }
            }
        }

        protected void add_s_btn_Click(object sender, EventArgs e)
        {

        }
    }
}