using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Lab_05a.Controllers
{
    public class MResearchController : Controller
    {
        [HttpGet]
        public void M01(int? id)
        {
            this.Response.Write("GET:M01");
            this.Response.End();
        }

        [HttpGet]
        public void M02(int? id)
        {
            this.Response.Write("GET:M02");
            this.Response.End();
        }

        [HttpGet]
        public void M03(int? id)
        {
            this.Response.Write("GET:M03");
            this.Response.End();
        }

        [HttpGet]
        public void MXX()
        {
            this.Response.Write("MXX");
            this.Response.End();
        }
    }
}