using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Web;
using System.Web.Mvc;

namespace Lab_05a.Controllers {
    public class CResearchController: Controller {

        [AcceptVerbs(HttpVerbs.Get | HttpVerbs.Post)]
        public void C01() {

            HttpContext.Response.Write($@"Request method: {HttpContext.Request.HttpMethod}.<br />");

            if (HttpContext.Request.QueryString.Count > 0) {
                HttpContext.Response.Write("Query params: <br />");
                foreach (string key in HttpContext.Request.QueryString.AllKeys) {
                    HttpContext.Response.Write($@"{key}: {HttpContext.Request.QueryString[key]}.<br />");
                }
            }

            HttpContext.Response.Write($@"Uri: {HttpContext.Request.Url.AbsoluteUri}.<br />");

            if (HttpContext.Request.Headers.Count > 0) {
                HttpContext.Response.Write("Headers: <br />");
                foreach (string key in HttpContext.Request.Headers.AllKeys) {
                    HttpContext.Response.Write($@"{key}: {HttpContext.Request.Headers[key]}.<br />");
                }
            }

            if (HttpContext.Request.HttpMethod == "POST") {
                using (StreamReader body = new StreamReader(HttpContext.Request.InputStream, Encoding.UTF8)) {
                    HttpContext.Response.Write($@"Body: {body.ReadToEnd()}.<br />");
                }
            }

            HttpContext.Response.End();
        }

        [AcceptVerbs(HttpVerbs.Get | HttpVerbs.Post)]
        public void C02() {
            HttpContext.Response.Write($@"Request method: {HttpContext.Request.HttpMethod}.<br />");
            HttpContext.Response.Write($@"Response code: {HttpContext.Response.StatusCode}.<br />");
            HttpContext.Response.Headers.Add("MyResponseHeader", "^_^");

            if (HttpContext.Response.Headers.Count > 0) {
                HttpContext.Response.Write("Headers: <br />");
                foreach (string key in HttpContext.Response.Headers.AllKeys) {
                    HttpContext.Response.Write($@"{key}: {HttpContext.Response.Headers[key]}.<br />");
                }
            }

            if (HttpContext.Request.HttpMethod == "POST") {
                using (StreamReader body = new StreamReader(HttpContext.Request.InputStream, Encoding.UTF8)) {
                    HttpContext.Response.Write($@"Body: {body.ReadToEnd()}.<br />");
                }
            }

            HttpContext.Response.End();
        }
    }
}