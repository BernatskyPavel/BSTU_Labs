using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Web;
using System.Web.Mvc;
using System.Web.Optimization;
using System.Web.Routing;

namespace Lab_05a {
    public class MvcApplication: System.Web.HttpApplication {
        protected void Application_Start() {
            AreaRegistration.RegisterAllAreas();
            FilterConfig.RegisterGlobalFilters(GlobalFilters.Filters);
            RouteConfig.RegisterRoutes(RouteTable.Routes);
        }

        protected void Application_Error() {
            var exception       = Server.GetLastError();
            var httpException   = exception as HttpException ?? new HttpException((Int32)HttpStatusCode.InternalServerError, "Internal Server Error", exception);
            var httpStatusCode  = httpException.GetHttpCode();

            Response.Clear();

            var routeData       = new RouteData();

            routeData.Values.Add("Controller", "MResearch");
            routeData.Values.Add("fromAppErrorEvent", true);
            routeData.Values.Add("ErrorMessage", httpException.Message);
            routeData.Values.Add("HttpStatusCode", httpStatusCode);

            routeData.Values.Add("action", "MXX");

            Server.ClearError();

            IController controller = new Controllers.MResearchController();

            controller.Execute(new RequestContext(new HttpContextWrapper(Context), routeData));
        }
    }
}
