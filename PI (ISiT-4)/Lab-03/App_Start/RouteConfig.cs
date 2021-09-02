using Lab_03.Routes;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Web.Routing;

namespace Lab_03
{
    public class RouteConfig
    {
        public static void RegisterRoutes(RouteCollection routes)
        {
            routes.IgnoreRoute("{resource}.axd/{*pathInfo}");

            routes.MapRoute(
                name: "Default",
                url: "{controller}/{action}/{id}",
                defaults: new { controller = "Dict", action = "Index", id = UrlParameter.Optional },
                constraints: new { controller = "Dict", action = "(Index)|(Add)|(AddSave)|(Delete)|(DeleteSave)|(Update)|(UpdateSave)" }
            );

            Route mrRoute = new Route("{*url}",
                                      new RouteValueDictionary { { "controller", "Dict" }, { "action", "Error"}, { "url", UrlParameter.Optional } },
                                      new AnyOtherUrlRouter());

            routes.Add(mrRoute);

            /*routes.MapRoute(
                name: "404-PageNotFound",
                url: "{*any}",
                defaults: new { controller = "Dict", action = "Error" }
            );*/
        }
    }
}
