using Lab_05b.Filters;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Lab_05b.Controllers {
    [RoutePrefix("ita")]
    public class AResearchController: Controller {
        [AcceptVerbs(HttpVerbs.Get), Route("aa"), ActionFilterBPV]
        public void AA() {
            this.HttpContext.Response.Write("Some stuff from action AA!</br>");
        }
        [AcceptVerbs(HttpVerbs.Get), Route("ar"), ResultFilterBPV]
        public void AR() {
            this.HttpContext.Response.Write("Some stuff from action AR!</br>");
        }
        [AcceptVerbs(HttpVerbs.Get), Route("ae/{n:int}"), ExceptionFilterBPV]
        public void AE(int n) {
            this.HttpContext.Response.Write($@"Some stuff from action AE: {1 / n}!</br>");
        }
    }
}