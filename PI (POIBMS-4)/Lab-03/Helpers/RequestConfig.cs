using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Reflection;
using System.Collections.Specialized;

namespace Lab_03.Helpers
{
    public class RequestConfig
    {
        public int? Min_id { get; set; }
        public int? Max_id { get; set; }
        public string Sort { get; set; }
        public int? Limit { get; set; }
        public int? Offset { get; set; }
        public string Like { get; set; }
        public string Globalike { get; set; }
        public string Columns { get; set; }

        public RequestConfig()
        {
            this.Min_id = null;
            this.Max_id = null;
            this.Sort = null;
            this.Limit = null;
            this.Offset = null;
            this.Like = null;
            this.Globalike = null;
            this.Columns = null;
        }

        public void ProcessRequestParams(NameValueCollection parameters)
        {
            if (parameters == null) return;
            if (int.TryParse(parameters["min_id"], out int value))
                this.Min_id = value;
            if (int.TryParse(parameters["max_id"], out value))
                this.Max_id = value;
            if (int.TryParse(parameters["offset"], out value))
                this.Offset = value;
            if (int.TryParse(parameters["limit"], out value))
                this.Limit = value;
            else this.Limit = 10;
            this.Sort = parameters["sort"];
            this.Like = parameters["like"];
            this.Globalike = parameters["globalike"];
            this.Columns = parameters["columns"];
        }

        public override string ToString()
        {
            string result = string.Empty;
            PropertyInfo[] info = this.GetType().GetProperties();
            foreach (PropertyInfo property in info)
            {
                if (property.GetValue(this) != default)
                {
                    //Convert.ChangeType(property.GetValue(this), property.GetType())
                    result += $@"&{property.Name.ToLower()}={property.GetValue(this)}";
                }
            }
            return result.Substring(1);
        }
    }
}