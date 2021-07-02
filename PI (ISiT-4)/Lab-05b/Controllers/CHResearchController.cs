using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Lab_05b.Controllers
{
    [RoutePrefix("itch")]
    public class CHResearchController : Controller
    {
        // GET: CHResearch
        public ActionResult Index()
        {
            return View();
        }
        [AcceptVerbs(HttpVerbs.Get)]
        [Route("ad")]
        [OutputCache(Duration = 5)]
        public void AD()
        {
            HttpContext.Response.Write($@"Current time is {DateTime.Now.TimeOfDay}");
        }
        [AcceptVerbs(HttpVerbs.Post)]
        [Route("ap")]
        [OutputCache(Duration = 7)]
        public void AP()
        {
            HttpContext.Response.Write($@"Current time is {DateTime.Now.TimeOfDay}, x = {HttpContext.Request.Params["x"] ?? "Empty"}, y = {HttpContext.Request.Params["y"] ?? "Empty"}");
        }
    }
}