using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Web.Routing;
using System.Web.SessionState;
using Lab_03.App_Code;

namespace Lab_03.Routes
{
    public class AnyOtherUrlRouter : IRouteHandler
    {
        private IControllerFactory _controllerFactory;

        public AnyOtherUrlRouter() { }
        public AnyOtherUrlRouter(IControllerFactory controllerFactory)
        {
            this._controllerFactory = controllerFactory;
        }

        protected virtual IHttpHandler GetHttpHandler(RequestContext requestContext)
        {
            requestContext.HttpContext.SetSessionStateBehavior(GetSessionStateBehavior(requestContext));
            return new AnyOtherUrlHandler(requestContext);
        }

        protected virtual SessionStateBehavior GetSessionStateBehavior(RequestContext requestContext)
        {
            string controllerName = (string)requestContext.RouteData.Values["controller"];
            IControllerFactory controllerFactory = this._controllerFactory ?? ControllerBuilder.Current.GetControllerFactory();
            return controllerFactory.GetControllerSessionBehavior(requestContext, controllerName);
        }

        IHttpHandler IRouteHandler.GetHttpHandler(RequestContext requestContext)
        {
            return GetHttpHandler(requestContext);
        }
    }
}