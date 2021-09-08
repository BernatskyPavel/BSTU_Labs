using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.IO;
using Newtonsoft.Json;
using WebClients.Helpers;
using System.Text;

namespace WebClients.LabViews
{
    public partial class Lab_01 : Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if(!IsPostBack)
            {
                Context.Session.Add("cookies", new CookieContainer());
            }
        }

        protected void POSTBtn_Click(object sender, EventArgs e)
        {
            customerr1.Visible = false;
            customerr2.Visible = false;
            HttpWebRequest myReq = (HttpWebRequest)WebRequest.Create("http://localhost:789/PI-POIBMS-4/Lab-01/rest.bpv");
            myReq.Method = "POST";
            myReq.CookieContainer = (CookieContainer)Context.Session["cookies"];
            myReq.ContentType = "application/x-www-form-urlencoded";
            if (Result.Text.Length > 0)
            {
                byte[] param = Encoding.UTF8.GetBytes($"result={int.Parse(Result.Text)}");
                myReq.GetRequestStream().Write(param, 0, param.Length);
            } else
            {
                myReq.ContentLength = 0;
            }

            HttpWebResponse myRes = (HttpWebResponse)myReq.GetResponse();
            Response json_response = null;
            using (StreamReader reader = new StreamReader(myRes.GetResponseStream()))
            {
                string body = reader.ReadToEnd();
                json_response = JsonConvert.DeserializeObject<Response>(body);
                //GetResult.Text = json_response.result.Value.ToString();
            }
            if (json_response.status != "Success")
            {
                customerr1.Text = json_response.message;
                customerr1.Visible = true;
            }
        }

        protected void GETBtn_Click(object sender, EventArgs e)
        {
            customerr1.Visible = false;
            customerr2.Visible = false;
            HttpWebRequest myReq = (HttpWebRequest)WebRequest.Create("http://localhost:789/PI-POIBMS-4/Lab-01/rest.bpv");
            myReq.Method = "GET";
            myReq.CookieContainer = (CookieContainer)Context.Session["cookies"];
            HttpWebResponse myRes = (HttpWebResponse)myReq.GetResponse();
            if (myRes.StatusCode == HttpStatusCode.OK)
            {
                using (StreamReader reader = new StreamReader(myRes.GetResponseStream()))
                {
                    string body = reader.ReadToEnd();
                    Response json_response = JsonConvert.DeserializeObject<Response>(body);
                    GetResult.Text = json_response.result.Value.ToString();
                }
            }
        }

        protected void PUTBtn_Click(object sender, EventArgs e)
        {
            customerr1.Visible = false;
            customerr2.Visible = false;
            HttpWebRequest myReq = (HttpWebRequest)WebRequest.Create("http://localhost:789/PI-POIBMS-4/Lab-01/rest.bpv");
            myReq.Method = "PUT";
            myReq.CookieContainer = (CookieContainer)Context.Session["cookies"];
            myReq.ContentType = "application/x-www-form-urlencoded";
            if (Add.Text.Length > 0)
            {
                byte[] param = Encoding.UTF8.GetBytes($"add={int.Parse(Add.Text)}");
                myReq.GetRequestStream().Write(param, 0, param.Length);
            } else
            {
                myReq.ContentLength = 0;
            }

            HttpWebResponse myRes = (HttpWebResponse)myReq.GetResponse();
            Response json_response = null;
            using (StreamReader reader = new StreamReader(myRes.GetResponseStream()))
            {
                string body = reader.ReadToEnd();
                json_response = JsonConvert.DeserializeObject<Response>(body);
                //GetResult.Text = json_response.result.Value.ToString();
            }
            if (json_response.status != "Success")
            {
                customerr2.Text = json_response.message;
                customerr2.Visible = true;
            }
        }

        protected void DELETEBtn_Click(object sender, EventArgs e)
        {
            customerr1.Visible = false;
            customerr2.Visible = false;
            HttpWebRequest myReq = (HttpWebRequest)WebRequest.Create("http://localhost:789/PI-POIBMS-4/Lab-01/rest.bpv");
            myReq.Method = "DELETE";
            myReq.CookieContainer = (CookieContainer)Context.Session["cookies"];
            HttpWebResponse myRes = (HttpWebResponse)myReq.GetResponse();
            Response json_response = null;
            using (StreamReader reader = new StreamReader(myRes.GetResponseStream()))
            {
                string body = reader.ReadToEnd();
                json_response = JsonConvert.DeserializeObject<Response>(body);
                //GetResult.Text = json_response.result.Value.ToString();
            }
            if (json_response.status != "Success")
            {
                customerr2.Text = json_response.message;
                customerr2.Visible = true;
            }
        }
    }
}