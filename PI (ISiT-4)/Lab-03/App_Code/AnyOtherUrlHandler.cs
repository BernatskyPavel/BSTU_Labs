using System;
using System.Globalization;
using System.Web;
using System.Web.Mvc;
using System.Web.Routing;
using System.Web.SessionState;

namespace Lab_03.App_Code
{
    public class AnyOtherUrlHandler : IHttpHandler, IRequiresSessionState
    {
        /// <summary>
        /// You will need to configure this handler in the Web.config file of your 
        /// web and register it with IIS before being able to use it. For more information
        /// see the following link: https://go.microsoft.com/?linkid=8101007
        /// </summary>
        #region IHttpHandler Members

        public bool IsReusable => throw new NotImplementedException();
        private RequestContext _requestContext;

        public AnyOtherUrlHandler(RequestContext requestContext)
        {
            this._requestContext = requestContext;
        }

        public AnyOtherUrlHandler()
        {
        }

        void IHttpHandler.ProcessRequest(HttpContext httpContext)
        {
            ProcessRequest(httpContext);
        }

        protected virtual void ProcessRequest(HttpContext httpContext)
        {
            HttpContextBase iHttpContext = new HttpContextWrapper(httpContext);
            ProcessRequest(iHttpContext);
        }

        protected internal virtual void ProcessRequest(HttpContextBase httpContext)
        {
            httpContext.Session.Add("Last-Method", _requestContext.HttpContext.Request.HttpMethod);
            httpContext.Session.Add("Last-Url", _requestContext.HttpContext.Request.Url.ToString());

            string controller_name = (string)_requestContext.RouteData.Values["controller"];
        
            IControllerFactory factory = ControllerBuilder.Current.GetControllerFactory();
            IController controller = factory.CreateController(_requestContext, controller_name);
            if (controller == null)
            {
                throw new InvalidOperationException(String.Format(
                    CultureInfo.CurrentCulture,
                    "NULL",
                    factory.GetType(),
                    controller_name));
            }
            try
            {
                controller.Execute(_requestContext);
            }
            finally
            {
                factory.ReleaseController(controller);
            }
        }

        #endregion
    }
}
