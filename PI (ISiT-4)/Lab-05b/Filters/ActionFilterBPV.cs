using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Lab_05b.Filters
{
    public class ActionFilterBPV : ActionFilterAttribute {

        public override void OnActionExecuted(ActionExecutedContext filterContext)
        {
            filterContext.HttpContext.Response.Write("Bye from Action filter!<br/>");
            base.OnActionExecuted(filterContext);
        }

        public override void OnActionExecuting(ActionExecutingContext filterContext)
        {
            filterContext.HttpContext.Response.Write("Hello from Action filter!<br/>");
            base.OnActionExecuting(filterContext);
        }

    }
}