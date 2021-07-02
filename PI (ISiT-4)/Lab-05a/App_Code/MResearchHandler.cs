using Lab_05a.Utils;
using Microsoft.Web.Infrastructure.DynamicValidationHelper;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Reflection;
using System.Web;
using System.Web.Mvc;
using System.Web.Routing;

namespace Lab_05a.App_Code
{
    public class MResearchHandler : IHttpHandler
    {
        public bool IsReusable => throw new NotImplementedException();
        private RequestContext _requestContext;

        public MResearchHandler(RequestContext requestContext)
        {
            this._requestContext = requestContext;
        }

        public MResearchHandler()
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
            string controller_name = (string)_requestContext.RouteData.Values["controller"];
            string action_name = (string)_requestContext.RouteData.Values["action"];
            string _action = string.Empty;
            if (_requestContext.RouteData.Values["api"] != null)
            {
                switch (_requestContext.RouteData.Values["api"] ?? "")
                {
                    case "V1": _action = "M01"; break;
                    case "V2": _action = "M02"; break;
                    case "V3": _action = "M03"; break;
                    default: _action = "M01"; break;
                }
            }
            if (controller_name == Consts.DEFAULT_CONTROLLER)
            {
                _requestContext.RouteData.Values["controller"] = controller_name = "MResearch";
            }
            if (action_name == Consts.DEFAULT_ACTION)
            {
                if (_action == string.Empty)
                {
                    _action = action_name == Consts.DEFAULT_ACTION ? "M01" : action_name;
                }

                _requestContext.RouteData.Values["action"] = _action;
            }
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
    }
}