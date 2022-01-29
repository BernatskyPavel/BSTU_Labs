using Lab_08.Controllers;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace Lab_08.Helpers {
    public static class RPCServicesDictionary {
        public static readonly Dictionary<string, dynamic> Services = new Dictionary<string, dynamic>() {
            {"GetM", typeof(JRService)}
        };
    }
}