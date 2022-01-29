using System;
using System.Web;

namespace Lab_01a.App_Code {
    public class BPVHandler: IHttpHandler {
        #region IHttpHandler Members

        public bool IsReusable {
            get {
                return true;
            }
        }

        public void ProcessRequest(HttpContext context) {
            context.Response.ContentType = "plain/text";
            context.Response.Write($"{context.Request.HttpMethod}-Http-BPV:ParmA = {context.Request.Params["ParmA"] ?? string.Empty},ParmB = {context.Request.Params["ParmB"] ?? string.Empty}");
            context.Response.End();
        }

        #endregion
    }
}
