using System;
using System.IO;
using System.Web;
using System.Text.RegularExpressions;

namespace Lab_01a.App_Code {
    public class MathHandler: IHttpHandler {
        private class Body {
            public double x {
                get; set;
            }
            public double y {
                get; set;
            }
        }

        #region IHttpHandler Members
        public bool IsReusable {
            get {
                return true;
            }
        }

        public void ProcessRequest(HttpContext context) {
            double d_x = 0.0, d_y = 0.0;
            if (!double.TryParse(context.Request.Params["x"], out d_x) || !double.TryParse(context.Request.Params["y"], out d_y)) {

                Stream stream = context.Request.InputStream;
                int stream_len = Convert.ToInt32(stream.Length);
                byte[] buffer = new byte[stream_len];
                int stream_read = stream.Read(buffer, 0, stream_len);

                string body = string.Empty;

                for (int i = 0; i < stream_len; i++) {
                    body = body + Convert.ToChar(buffer[i]);
                }

                Regex regex = new Regex($@"""(?<name>[xy])"" *: *""(?<num>\d+(,\d+)*)""");
                MatchCollection matches = regex.Matches(body);
                bool result = true;
                if (matches.Count == 2) {
                    foreach (Match m in matches) {
                        if (m.Success && m.Groups["name"].Value == "x") {
                            result &= double.TryParse(m.Groups["num"].Value, out d_x);
                        }
                        if (m.Success && m.Groups["name"].Value == "y") {
                            result &= double.TryParse(m.Groups["num"].Value, out d_y);
                        }
                    }
                }
                else {
                    result = false;
                }
                if (!result) {
                    context.Response.StatusCode = 400;
                    context.Response.End();
                    return;
                }
            }

            context.Response.StatusCode = 200;
            context.Response.Write($@"{d_x + d_y}");
            context.Response.End();

        }

        #endregion
    }
}
