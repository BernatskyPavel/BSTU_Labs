using System;
using System.Net;
using System.Web;

namespace Lab_01a.App_Code
{
    public class FMHandler : IHttpHandler
    {
        /// <summary>
        /// You will need to configure this handler in the Web.config file of your 
        /// web and register it with IIS before being able to use it. For more information
        /// see the following link: https://go.microsoft.com/?linkid=8101007
        /// </summary>
        /// 

        private static readonly WebClient client = new WebClient();

        #region IHttpHandler Members

        public bool IsReusable
        {
            // Return false in case your Managed Handler cannot be reused for another request.
            // Usually this would be false in case you have some state information preserved per request.
            get { return true; }
        }

        public void ProcessRequest(HttpContext context)
        {
            switch (context.Request.HttpMethod)
            {
                case "POST":

                    double d_x = 0.0, d_y = 0.0;
                    if (!double.TryParse(context.Request.Params["x"], out d_x) || !double.TryParse(context.Request.Params["y"], out d_y))
                    {
                        context.Response.StatusCode = 400;
                        context.Response.End();
                        return;
                    }

                    context.Response.ContentType = "text/plain";
                    context.Response.StatusCode = 200;
                    context.Response.Write($@"Result: {d_x * d_y}.");
                    context.Response.End();
                    break;
                case "GET":
                    byte[] buffer;
                    client.Credentials = new NetworkCredential("anonymous", "janeDoe@example.com");
                    try
                    {
                        buffer = client.DownloadData(new Uri("ftp://localhost:821/PI-ISiT-4/Lab-01a/html/FMPage.html"));
                    }
                    catch (WebException e)
                    {
                        context.Response.StatusCode = 400;
                        context.Response.Write(e.Message);
                        context.Response.End();
                        return;
                    }
                    context.Response.ContentType = "text/html";
                    context.Response.StatusCode = 200;
                    context.Response.BinaryWrite(buffer);
                    context.Response.End();
                    break;
                default:
                    break;
            }
        }

        #endregion
    }
}
