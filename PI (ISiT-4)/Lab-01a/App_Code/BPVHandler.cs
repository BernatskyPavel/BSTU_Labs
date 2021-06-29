using System;
using System.Web;

namespace Lab_01a.App_Code
{
    public class BPVHandler : IHttpHandler
    {
        /// <summary>
        /// You will need to configure this handler in the Web.config file of your 
        /// web and register it with IIS before being able to use it. For more information
        /// see the following link: https://go.microsoft.com/?linkid=8101007
        /// </summary>
        #region IHttpHandler Members

        public bool IsReusable
        {
            // Return false in case your Managed Handler cannot be reused for another request.
            // Usually this would be false in case you have some state information preserved per request.
            get { return true; }
        }

        public void ProcessRequest(HttpContext context)
        {
            context.Response.ContentType = "plain/text";
            context.Response.Write($"{context.Request.HttpMethod}-Http-BPV:ParmA = {context.Request.Params["ParmA"]??""},ParmB = {context.Request.Params["ParmB"]??""}");
            context.Response.End();
        }

        #endregion
    }
}
