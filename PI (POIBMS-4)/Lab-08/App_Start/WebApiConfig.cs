using Lab_08.Helpers;
using Lab_08.Models;
using Newtonsoft.Json.Serialization;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Http;

namespace Lab_08 {
    public static class WebApiConfig {

        public static string UrlPrefix {
            get {
                return "jsonrpc";
            }
        }
        public static string UrlPrefixRelative {
            get {
                return "~/jsonrpc";
            }
        }

        public static void Register(HttpConfiguration config) {
            // Web API configuration and services

            config.Formatters.JsonFormatter.SerializerSettings.NullValueHandling = Newtonsoft.Json.NullValueHandling.Ignore;
            config.Formatters.JsonFormatter.SerializerSettings.MissingMemberHandling = Newtonsoft.Json.MissingMemberHandling.Error;
            config.Formatters.JsonFormatter.SerializerSettings.DefaultValueHandling = Newtonsoft.Json.DefaultValueHandling.Ignore;
            config.Formatters.JsonFormatter.SerializerSettings.Error = delegate (object sender, ErrorEventArgs args) {
                SerializerErrorsHolder.Errors.Enqueue(args.ErrorContext.Error.Message);
                args.ErrorContext.Handled = true;
            };

            // Web API routes
            config.MapHttpAttributeRoutes();

            //config.Routes.MapHttpRoute(
            //    name: "DefaultApi",
            //    routeTemplate: WebApiConfig.UrlPrefix+"/{controller}/{id}",
            //    defaults: new {
            //        id = RouteParameter.Optional
            //    }
            //);
        }
    }
}
