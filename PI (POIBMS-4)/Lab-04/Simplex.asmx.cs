using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Script.Services;
using System.Web.Services;

namespace Lab_04
{
    /// <summary>
    /// Summary description for Simplex
    /// </summary>
    [WebService(Namespace = "http://BPV/", Description = "Simple service for Lab-04.")]
    [WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
    [System.ComponentModel.ToolboxItem(false)]
    [ScriptService()]
    // To allow this Web Service to be called from script, using ASP.NET AJAX, uncomment the following line. 
    // [System.Web.Script.Services.ScriptService]
    public class Simplex : System.Web.Services.WebService
    {

        [WebMethod(Description = "Returns the sum of two integers.")]
        public int Add(int x, int y)
        {
            return x + y;
        }

        [WebMethod(Description = "Returns the concatination of two strings.")]
        public string Concat(string s, double d)
        {
            return $"{s}{d}";
        }

        [WebMethod(Description = "Returns the sum of two custom A classes.")]
        public A Sum(A a1, A a2)
        {
            return new A
            {
                S = $"{a1.S}{a2.S}",
                K = a1.K + a2.K,
                F = a1.F + a2.F,
            };
        }

        [ScriptMethod(ResponseFormat = ResponseFormat.Json, UseHttpGet = false)]
        [WebMethod(Description = "Returns the sum of two integers in JSON.")]
        public int AddS(int a, int b)
        {
            return a + b;
        }

        public class A
        {
            public string S;
            public int K;
            public float F;
        }
    }
}
