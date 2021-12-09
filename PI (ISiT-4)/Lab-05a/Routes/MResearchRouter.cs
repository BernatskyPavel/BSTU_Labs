using Lab_05a.App_Code;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Web.Routing;
using System.Web.SessionState;

namespace Lab_05a.Routes {
    public class MResearchRouter: IRouteHandler {
        private IControllerFactory _controllerFactory;

        public MResearchRouter() {
        }

        public MResearchRouter(IControllerFactory controllerFactory) {
            this._controllerFactory = controllerFactory;
        }

        protected virtual IHttpHandler GetHttpHandler(RequestContext requestContext) {
            requestContext.HttpContext.SetSessionStateBehavior(GetSessionStateBehavior(requestContext));
            
            return new MResearchHandler(requestContext);
        }

        protected virtual SessionStateBehavior GetSessionStateBehavior(RequestContext requestContext) {
            string controllerName                   = (string)requestContext.RouteData.Values["controller"];
            IControllerFactory controllerFactory    = this._controllerFactory ?? ControllerBuilder.Current.GetControllerFactory();
            
            return controllerFactory.GetControllerSessionBehavior(requestContext, controllerName);
        }

        IHttpHandler IRouteHandler.GetHttpHandler(RequestContext requestContext) {
            return GetHttpHandler(requestContext);
        }
    }
}