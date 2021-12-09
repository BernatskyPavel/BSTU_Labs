using Lab_05a.Constraints;
using Lab_05a.Routes;
using Lab_05a.Utils;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Web.Routing;

namespace Lab_05a {
    public class RouteConfig {
        public static void RegisterRoutes(RouteCollection routes) {
            routes.IgnoreRoute("{resource}.axd/{*pathInfo}");

            Route mrRoute =     new Route("{api}/{controller}/{prefix}/{action}/{id}",
                                      new RouteValueDictionary { { "controller", Consts.DEFAULT_CONTROLLER }, { "action", Consts.DEFAULT_ACTION }, { "api", UrlParameter.Optional }, { "prefix", UrlParameter.Optional }, { "id", UrlParameter.Optional } },
                                      new RouteValueDictionary { { "api", @"V3" }, { "prefix", "X" }, { "controller", $@"({Consts.DEFAULT_ACTION})|MResearch" } },
                                      new MResearchRouter());
            Route mrRoute3 =    new Route("{controller}/{action}/{id}",
                                      new RouteValueDictionary { { "controller", Consts.DEFAULT_CONTROLLER }, { "action", Consts.DEFAULT_ACTION }, { "id", UrlParameter.Optional } },
                                      new RouteValueDictionary { { "action", $@"({Consts.DEFAULT_ACTION})|M[0-9X]+" }, { "controller", $@"({Consts.DEFAULT_ACTION})|MResearch" } },
                                      new MResearchRouter());
            Route mrRoute4 =    new Route("{api}/{controller}/{action}",
                                      new RouteValueDictionary { { "controller", Consts.DEFAULT_CONTROLLER }, { "action", Consts.DEFAULT_ACTION }, { "api", "V1" } },
                                      new RouteValueDictionary { { "api", @"V[1-3]{1}" }, { "action", $@"({Consts.DEFAULT_ACTION})|M[0-9X]+" }, { "controller", $@"({Consts.DEFAULT_ACTION})|MResearch" } },
                                      new MResearchRouter());
            routes.Add(mrRoute4);
            routes.Add(mrRoute3);
            routes.Add(mrRoute);

            routes.MapRoute(
                name: "CResearch",
                url: "{controller}/{action}/{id}",
                defaults: new {
                    controller = "CResearch",
                    action = "C01",
                    id = UrlParameter.Optional
                },
                constraints: new {
                    controller = new NotMResearch()
                }
            );
        }
    }
}
