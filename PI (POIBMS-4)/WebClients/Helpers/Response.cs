using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using Newtonsoft.Json;  

namespace WebClients.Helpers
{
    public class Response
    {
        public string status { get; set; }
        public int? result { get; set; }
        public string message { get; set; }
    }
}