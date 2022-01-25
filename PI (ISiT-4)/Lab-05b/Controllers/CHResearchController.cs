using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Lab_05b.Controllers {
    [RoutePrefix("itch")]
    public class CHResearchController: Controller {
        [AcceptVerbs(HttpVerbs.Get), Route("ad"), OutputCache(Duration = 5)]
        public void AD() {
            this.HttpContext.Response.Write($@"Current time is {DateTime.Now.TimeOfDay}");
        }

        [AcceptVerbs(HttpVerbs.Post), Route("ap"), OutputCache(Duration = 7, VaryByParam = "x;y")]
        public void AP() {
            this.HttpContext.Response.Write($@"Current time is {DateTime.Now.TimeOfDay}, x = {this.HttpContext.Request.Params["x"] ?? "Empty"}, y = {this.HttpContext.Request.Params["y"] ?? "Empty"}");
        }
    }
}