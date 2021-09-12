using System;
using System.Collections.Generic;
using System.Web;
using System.Web.SessionState;

namespace Lab_01.App_Code
{
    public class RESTHandler : IHttpHandler, IRequiresSessionState
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
            if (context.Application.Get("Result") == null)
            {
                context.Application.Add("Result", 0);
            }
            if (context.Session["Stack"] == null)
            {
                context.Session["Stack"] = new Stack<int>();
            }
            int response = (int)context.Application.Get("Result");
            string error_msg = string.Empty;
            bool is_error = false;
            context.Response.ContentType = "application/json";
            context.Response.StatusCode = 200;
            switch (context.Request.HttpMethod) {
                case "GET":
                    {
                        Stack<int> temp = (Stack<int>)context.Session["Stack"];
                        if (temp.Count != 0)
                        {
                            response += temp.Peek();
                        }
                    }
                    break;
                case "POST":
                    {
                        if (context.Request.Params["Result"] != null)
                        {
                            int x = 0;
                            bool is_succ = int.TryParse(context.Request.Params["Result"], out x);
                            if (!is_succ)
                            {
                                is_error = true;
                                error_msg = "Wrong type of parameter!";
                                break;
                            }
                            context.Application.Set("Result", x);
                            break;
                        } else
                        {
                            is_error = true;
                            error_msg = "Missing Result parameter!";
                        }
                    }
                    break;
                case "PUT":
                    {
                        if (context.Request.Params["Add"] != null)
                        {
                            int x = 0;
                            bool is_succ = int.TryParse(context.Request.Params["Add"], out x);
                            if (!is_succ)
                            {
                                is_error = true;
                                error_msg = "Wrong type of parameter!";
                                break;
                            }
                            Stack<int> temp = (Stack<int>)context.Session["Stack"];
                            temp.Push(x);
                        } else
                        {
                            is_error = true;
                            error_msg = "Missing Add parameter!";
                        }
                    }
                    break;
                case "DELETE":
                    {
                        Stack<int> temp = (Stack<int>)context.Session["Stack"];
                        if (temp.Count == 0 )
                        {
                            is_error = true;
                            error_msg = "Stack already empty!";
                            break;
                        }
                        temp.Pop();
                    }
                    break;
                default:
                    context.Response.StatusCode = 501;
                    break;
            }
            if (!is_error)
            {
                if (context.Request.HttpMethod == "GET")
                {
                    context.Response.Write($@"{{ ""Status"":""Success"", ""Result"":{response} }}");
                }
                else
                {
                    context.Response.Write($@"{{ ""Status"" : ""Success"" }}");
                }
            } else
            {
                context.Response.Write($@"{{ ""Status"":""Error"", ""Message"":""{error_msg}"" }}");
            }
            context.Response.End();
        }
        #endregion
    }
}
