using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Lab_05b.Controllers
{
    [RoutePrefix("it")]
    public class MResearchController : Controller
    {
        // GET: MResearch
        public ActionResult Index()
        {
            return View();
        }

        [Route("{n:int}/{str}")]
        [AcceptVerbs(HttpVerbs.Get)]
        public void M01(int n, string str)
        {
            HttpContext.Response.Write($@"{HttpContext.Request.HttpMethod}:M01:/{n}/{str}.<br />");
            HttpContext.Response.End();
        }

        [Route("{b:bool}/{letters:alpha}")]
        [AcceptVerbs(HttpVerbs.Get | HttpVerbs.Post)]
        public void M02(bool b, string letters)
        {
            HttpContext.Response.Write($@"{HttpContext.Request.HttpMethod}:M02:/{b}/{letters}.<br />");
            HttpContext.Response.End();
        }

        [Route("{f:float}/{str:minlength(2):maxlength(5)}")]
        [AcceptVerbs(HttpVerbs.Get | HttpVerbs.Delete)]
        public void M03(float f, string str)
        {
            HttpContext.Response.Write($@"{HttpContext.Request.HttpMethod}:M03:/{f}/{str}.<br />");
            HttpContext.Response.End();
        }

        [Route("{letters:alpha:minlength(3):maxlength(4)}/{n:range(100,200)}")]
        [AcceptVerbs(HttpVerbs.Put)]
        public void M04(string letters, int n)
        {
            HttpContext.Response.Write($@"{HttpContext.Request.HttpMethod}:M04:/{letters}/{n}.<br />");
            HttpContext.Response.End();
        }

        [Route(@"{mail:regex(^[^@\s]+@[^@\s]+\.[^@\s]+$)}")]
        [AcceptVerbs(HttpVerbs.Post)]
        public void M04(string mail)
        {
            HttpContext.Response.Write($@"{HttpContext.Request.HttpMethod}:{mail}.<br />");
            HttpContext.Response.End();
        }
    }
}