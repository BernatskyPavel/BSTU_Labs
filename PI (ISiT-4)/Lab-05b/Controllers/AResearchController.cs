using Lab_05b.Filters;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Lab_05b.Controllers
{
    [RoutePrefix("ita")]
    public class AResearchController : Controller
    {
        // GET: AResearch
        public ActionResult Index()
        {
            return View();
        }
        [AcceptVerbs(HttpVerbs.Get)]
        [Route("aa")]
        [ActionFilterBPV]
        public void AA()
        {
            HttpContext.Response.Write("Some stuff from action AA!</br>");
        }
        [AcceptVerbs(HttpVerbs.Get)]
        [Route("ar")]
        [ResultFilterBPV]
        public void AR()
        {
            HttpContext.Response.Write("Some stuff from action AR!</br>");
        }
        [Route("ae/{n:int}")]
        [AcceptVerbs(HttpVerbs.Get)]
        [ExceptionFilterBPV]
        public void AE(int n)
        {
            HttpContext.Response.Write($@"Some stuff from action AE: {1/n}!</br>");
        }
    }
}