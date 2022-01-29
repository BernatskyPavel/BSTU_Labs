using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Web;
using System.IO;
using Newtonsoft.Json;
using System.Threading;
using System.Net;

namespace Lab_03.Models
{
    public class DictContext
    {
        public List<Record> Records { get; set; }
        private Timer timer;
        public DictContext()
        {
            FtpWebRequest ftp_request = (FtpWebRequest)WebRequest.Create(System.Configuration.ConfigurationManager.AppSettings["DictPath"]);
            ftp_request.Method = WebRequestMethods.Ftp.DownloadFile;
            ftp_request.Credentials = new NetworkCredential("anonymous", "janeDoe@example.com");
            FtpWebResponse ftp_response;
            try
            {
                ftp_response = (FtpWebResponse)ftp_request.GetResponse();
                using (StreamReader file = new StreamReader(ftp_response.GetResponseStream()))
                {
                    using (JsonReader jsonReader = new JsonTextReader(file))
                    {
                        JsonSerializer serializer = new JsonSerializer();
                        serializer.NullValueHandling = NullValueHandling.Ignore;
                        Records = serializer.Deserialize<List<Record>>(jsonReader);
                    }
                }
            }
            catch (WebException)
            {
                Records = new List<Record>();
                Serialize(null);
            }
            timer = new Timer(Serialize, null, 0, 60000);
        }

        ~DictContext()
        {
            timer.Dispose();
            Serialize(null);
        }

        private void Serialize(Object stateInfo)
        {
            Monitor.Enter(this);
            try
            {
                FtpWebRequest ftp_request = (FtpWebRequest)WebRequest.Create(System.Configuration.ConfigurationManager.AppSettings["DictPath"]);
                ftp_request.Credentials = new NetworkCredential("anonymous", "janeDoe@example.com");
                ftp_request.Method = WebRequestMethods.Ftp.UploadFile;
                using (StreamWriter file = new StreamWriter(ftp_request.GetRequestStream()))
                {
                    using (JsonWriter jsonWriter = new JsonTextWriter(file))
                    {
                        JsonSerializer serializer = new JsonSerializer();
                        serializer.NullValueHandling = NullValueHandling.Ignore;
                        serializer.Serialize(jsonWriter, Records);
                    }
                }
                _ = ftp_request.GetResponse();
            }
            catch (WebException)
            {
            }
            Monitor.Exit(this);
        }
    }
}