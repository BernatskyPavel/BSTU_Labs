using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http.Formatting;
using System.Web;
using System.Web.Http;
using System.Web.Http.Controllers;
using System.Web.Http.Filters;

namespace Lab_03.Filters
{
    public class FormatFilter : ActionFilterAttribute
    {
        private static readonly Dictionary<string, (string, MediaTypeFormatter)> type_dict = new Dictionary<string, (string, MediaTypeFormatter)> {
            { "json",( "application/json", GlobalConfiguration.Configuration.Formatters.JsonFormatter ) },
            { "xml", ("text/xml", GlobalConfiguration.Configuration.Formatters.XmlFormatter) }
        };

        public FormatFilter()
        {
        }

        public override void OnActionExecuting(HttpActionContext actionContext)
        {
            _ = actionContext.RequestContext.RouteData.Values.TryGetValue("ext", out object o_ext);
            (string, MediaTypeFormatter) type = type_dict[((string)o_ext??"json").ToLower()];
            actionContext.Request.Properties.Add("formatter", type);
            base.OnActionExecuting(actionContext);
        }
    }
}