using Lab_02.Helpers;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Text;
using System.Web;
using System.Web.Http;

namespace Lab_02.Controllers
{
    public class ValuesController : ApiController
    {
        private int Result;
        private Stack<int> vs;

        public ValuesController()
        {
            if (HttpContext.Current.Application["Result"] == null)
            {
                HttpContext.Current.Application.Add("Result", 0);
            }
            this.Result = (int)HttpContext.Current.Application["Result"];

            if (HttpContext.Current.Application["Stack"] == null)
            {
                HttpContext.Current.Application.Add("Stack", new Stack<int>());
            }
            this.vs = (Stack<int>)HttpContext.Current.Application["Stack"];


        }

        ~ValuesController()
        {
            HttpContext.Current.Application.Set("Result", this.Result);
            HttpContext.Current.Application.Set("Stack", this.vs);
        }

        // GET api/values
        [HttpGet]
        public HttpResponseMessage Get()
        {
            HttpResponseMessage response = Request.CreateResponse();
            response.Content = new StringContent($@"{{ ""Status"":""Success"", ""Result"":{this.Result + (this.vs.Count > 0 ? this.vs.Peek() : 0)} }}", Encoding.UTF8, "application/json");
            response.StatusCode = HttpStatusCode.OK;
            return response;
        }

        // POST api/values
        public HttpResponseMessage Post([FromBody] Parameters param)
        {
            HttpResponseMessage response = Request.CreateResponse();
            response.StatusCode = HttpStatusCode.OK;
            if (param.Result.HasValue)
            {
                this.Result = param.Result.Value;
                HttpContext.Current.Application.Set("Result", this.Result);
                response.Content = new StringContent($@"{{ ""Status"":""Success"" }}", Encoding.UTF8, "application/json");
            }
            else
            {
                response.Content = new StringContent($@"{{ ""Status"":""Error"", ""Message"":""Missing Result parameter!""  }}", Encoding.UTF8, "application/json");
            }

            return response;
        }

        // PUT api/values/5
        public HttpResponseMessage Put([FromBody] Parameters param)
        {
            HttpResponseMessage response = Request.CreateResponse();
            response.StatusCode = HttpStatusCode.OK;
            if (param.Add.HasValue)
            {
                this.vs.Push(param.Add.Value);
                response.Content = new StringContent($@"{{ ""Status"":""Success"" }}", Encoding.UTF8, "application/json");
            }
            else
            {
                response.Content = new StringContent($@"{{ ""Status"":""Error"", ""Message"":""Missing Add parameter!""  }}", Encoding.UTF8, "application/json");
            }

            return response;
        }

        // DELETE api/values/5
        public HttpResponseMessage Delete()
        {
            HttpResponseMessage response = Request.CreateResponse();
            response.StatusCode = HttpStatusCode.OK;
            if (this.vs.Count > 0)
            {
                _ = this.vs.Pop();
                response.Content = new StringContent($@"{{ ""Status"":""Success"" }}", Encoding.UTF8, "application/json");
            }
            else
            {
                response.Content = new StringContent($@"{{ ""Status"":""Error"", ""Message"":""Stack already empty!""  }}", Encoding.UTF8, "application/json");
            }

            return response;
        }
    }
}
