using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace Lab_08.Helpers {
    public static class SerializerErrorsHolder {
        public static Queue<string> Errors = new Queue<string> ();
    }
}