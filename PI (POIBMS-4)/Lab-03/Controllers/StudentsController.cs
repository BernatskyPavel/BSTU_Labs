using Lab_03.Context;
using Lab_03.Models;
using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Web;
using System.Web.Http;
using Newtonsoft.Json;
using System.Net.Http.Formatting;
using System.Reflection;
using Lab_03.Helpers;
using Lab_03.Filters;

namespace Lab_03.Controllers
{
    static class Extensions
    {
        public static IList<T> Clone<T>(this IList<T> listToClone) where T : ICloneable
        {
            return listToClone.Select(item => (T)item.Clone()).ToList();
        }
    }

    public class StudentsController : ApiController
    {

        private static PSQLStudentContext _context;
        private static Dictionary<string, (string, MediaTypeFormatter)> type_dict = new Dictionary<string, (string, MediaTypeFormatter)> {
            { "json",( "application/json", GlobalConfiguration.Configuration.Formatters.JsonFormatter ) },
            { "xml", ("text/xml", GlobalConfiguration.Configuration.Formatters.XmlFormatter) }
        };

        static StudentsController()
        {
            _context = new PSQLStudentContext();
        }

        [HttpGet]
        [Route("getc")]
        public string GetC()
        {
            RequestConfig config = new RequestConfig();
            config.ProcessRequestParams(HttpContext.Current.Request.Params);


            return config.ToString();
        }

        public HttpResponseMessage Get()
        {
            RequestConfig config = new RequestConfig();
            config.ProcessRequestParams(HttpContext.Current.Request.Params);

            List<StudentModel> collection = _context.Students.ToList();
            int origin_length = _context.Students.Count();
            collection.Sort((x, y) => x.Id.Value.CompareTo(y.Id.Value));

            if (null != config.Globalike)
            {
                collection = collection.FindAll(x => x.Concat().Contains(config.Globalike));
            }
            else if (null != config.Like)
            {
                collection = collection.FindAll(x => x.Name.Contains(config.Like));
            }

            if (config.Min_id.HasValue)
                collection = collection.FindAll(x => x.Id >= config.Min_id.Value);
            if (config.Max_id.HasValue)
                collection = collection.FindAll(x => x.Id <= config.Max_id.Value);

            if (config.Offset.HasValue)
                collection = collection.Skip(config.Offset.Value).ToList();
            if (config.Limit.HasValue)
                collection = collection.Take(config.Limit.Value).ToList();

            if (null != config.Sort)
            {
                switch (config.Sort.ToLower())
                {
                    case "asc":
                        collection.Sort((x, y) => x.Name.CompareTo(y.Name));
                        break;
                    case "desc":
                        collection.Sort((x, y) => y.Name.CompareTo(x.Name));
                        break;
                    default: break;
                }
            }

            collection = collection.Clone().ToList();
            string path = $@"{Request.RequestUri.Scheme}://{Request.RequestUri.Authority}{Request.RequestUri.LocalPath}";
            
            collection.ForEach(x =>
            {
                x.Links = x.Links ?? new List<LinkModel>();
                x.Links.Add(
                    new LinkModel
                    {
                        Action = "Get Student Info",
                        Method = "GET",
                        Url = $"{path}/{x.Id}".Replace("//", "/")
                    }
                );
            });

            List<LinkModel> links = new List<LinkModel>();

            if (config.Offset.HasValue && config.Offset.Value != 0)
            {
                int origin_limit = config.Limit.Value, origin_offset = config.Offset.Value;
                if (config.Offset.Value < config.Limit.Value)
                {
                    config.Offset = 0;
                }
                else
                {
                    config.Offset -= config.Limit;
                }

                links.Add(new LinkModel
                {
                    Action = $"Prev {config.Limit}",
                    Method = "GET",
                    Url = $"{path}?{config}",
                });

                config.Offset = origin_offset;
                config.Limit = origin_limit;

                int diff = origin_length - config.Offset.Value - config.Limit.Value;
                if (diff > 0)
                {
                    config.Offset += config.Limit.Value;
                    links.Add(new LinkModel
                    {
                        Action = $"Next {Math.Min(diff, config.Limit.Value)}",
                        Method = "GET",
                        Url = $"{path}?{config}",
                    });
                }
            }
            else
            {
                int diff = origin_length - config.Limit.Value;
                if (diff > 0)
                {
                    config.Offset = config.Limit.Value;
                    links.Add(new LinkModel
                    {
                        Action = $"Next {Math.Min(diff, config.Limit.Value)}",
                        Method = "GET",
                        Url = $"{path}?{config}",
                    });
                }

            }

            links.Add(new LinkModel
            {
                Action = $"Add Student",
                Method = "POST",
                Url = $"{path}",
            });

            if (null != config.Columns)
            {
                List<string> columns = config.Columns.Split(',').ToList();
                for (int i = 0; i < columns.Count(); i++)
                {
                    columns[i] = columns[i].Trim().ToLower();
                    columns[i] = char.ToUpper(columns[i][0]) + columns[i].Substring(1);
                }
                columns.Add("Links");
                PropertyInfo[] info = typeof(StudentModel).GetProperties();
                foreach (PropertyInfo property in info)
                {
                    if (!columns.Contains(property.Name))
                    {
                        collection.ForEach(x => property.SetValue(x, default));
                    }
                }
            }

            _ = Request.Properties.TryGetValue("formatter", out object value);
            (string, MediaTypeFormatter) type = ((string, MediaTypeFormatter))value;
            return new HttpResponseMessage()
            {
                Content = new ObjectContent<ResponseModel<StudentModel>>(
                    new ResponseModel<StudentModel>()
                    {
                        Collection = collection,
                        Links = links,
                    },
                    type.Item2,
                    type.Item1
                )
            };
        }

        public HttpResponseMessage Get(int id)
        {
            bool is_exist = false, is_deleted = true;
            string msg = string.Empty;
            StudentModel student = null;
            if (_context.Students.Any(x => x.Id == id))
            {
                is_exist = true;
                student = (StudentModel)_context.Students.First(x => x.Id == id).Clone();
            }

            bool is_error = false;

            if (!is_exist)
            {
                is_error = true;
                msg = "Student with such id didn't exist!";
            }
            else if (!is_deleted)
            {
                is_error = true;
            }
            List<LinkModel> links = null;
            if (!is_error)
            {
                links = new List<LinkModel>();
                string path = $@"{Request.RequestUri.Scheme}://{Request.RequestUri.Authority}{Request.RequestUri.LocalPath}";
                links.Add(new LinkModel
                {
                    Action = $"Update Student",
                    Method = "PUT",
                    Url = $"{path}",
                });
                links.Add(new LinkModel
                {
                    Action = $"Remove Student",
                    Method = "DELETE",
                    Url = $"{path}",
                });
                links.Add(new LinkModel
                {
                    Action = $"Back to List",
                    Method = "GET",
                    Url = $"{Request.Headers.Referrer}",
                });
            }

            _ = Request.Properties.TryGetValue("formatter", out object value);
            (string, MediaTypeFormatter) type = ((string, MediaTypeFormatter))value;
            return new HttpResponseMessage()
            {
                Content = new ObjectContent<ResponseModel<StudentModel>>(
                    new ResponseModel<StudentModel>()
                    {
                        Object = student,
                        Links = links,
                        Error = is_error ?
                        new ErrorModel
                        {
                            Message = msg
                        } : null
                    },
                    type.Item2,
                    type.Item1
                )
            };
        }

        public HttpResponseMessage Post([FromBody] StudentModel student)
        {
            _context.Students.Add(student);
            bool is_saved = true;
            string msg = string.Empty;
            try
            {
                _context.SaveChanges();
            }
            catch (Exception ex)
            {
                msg = ex.ToString();
                is_saved = false;
            }

            List<LinkModel> links = null;
            if (is_saved)
            {
                links = new List<LinkModel>();
                string path = $@"{Request.RequestUri.Scheme}://{Request.RequestUri.Authority}{Request.RequestUri.LocalPath}";
                links.Add(new LinkModel
                {
                    Action = $"Get Student Info",
                    Method = "GET",
                    Url = $"{path}{student.Id.Value}",
                });
                links.Add(new LinkModel
                {
                    Action = $"Back to List",
                    Method = "GET",
                    Url = $"{Request.Headers.Referrer}",
                });
            }

            _ = Request.Properties.TryGetValue("formatter", out object value);
            (string, MediaTypeFormatter) type = ((string, MediaTypeFormatter))value;

            return new HttpResponseMessage()
            {
                Content = new ObjectContent<ResponseModel<StudentModel>>(
                    new ResponseModel<StudentModel>()
                    {
                        Object = is_saved ? student : null,
                        Links = links,
                        Error = !is_saved ?
                        new ErrorModel
                        {
                            Message = msg
                        } : null
                    },
                    type.Item2,
                    type.Item1
                )
            };
        }

        public HttpResponseMessage Put(int id, [FromBody] StudentModel student)
        {
            bool is_exist = false, is_updated = true;
            string msg = string.Empty;
            StudentModel origin = null;
            if (_context.Students.Any(x => x.Id == id))
            {
                is_exist = true;
                StudentModel temp = _context.Students.First(x => x.Id == id);
                origin = (StudentModel)temp.Clone();
                temp.Name = student.Name;
                temp.Phone = student.Phone;
                try
                {
                    _context.SaveChanges();
                }
                catch (Exception ex)
                {
                    msg = ex.ToString();
                    is_updated = false;
                }
            }

            bool is_error = false;

            if (!is_exist)
            {
                is_error = true;
                msg = "Student with such id didn't exist!";
            }
            else if (!is_updated)
            {
                is_error = true;
            }

            List<LinkModel> links = null;
            if (!is_error)
            {
                links = new List<LinkModel>();
                string path = $@"{Request.RequestUri.Scheme}://{Request.RequestUri.Authority}{Request.RequestUri.LocalPath}";
                links.Add(new LinkModel
                {
                    Action = $"Get Student Info",
                    Method = "GET",
                    Url = $"{path}{student.Id.Value}",
                });
                links.Add(new LinkModel
                {
                    Action = $"Back to List",
                    Method = "GET",
                    Url = $"{Request.Headers.Referrer}",
                });
            }

            _ = Request.Properties.TryGetValue("formatter", out object value);
            (string, MediaTypeFormatter) type = ((string, MediaTypeFormatter))value;

            return new HttpResponseMessage()
            {
                Content = new ObjectContent<ResponseModel<StudentModel>>(
                    new ResponseModel<StudentModel>()
                    {
                        Object = !is_error ? origin : null,
                        Links = links,
                        Error = is_error ?
                        new ErrorModel
                        {
                            Message = msg
                        } : null
                    },
                    type.Item2,
                    type.Item1
                )
            };
        }

        public HttpResponseMessage Delete(int id)
        {
            bool is_exist = false, is_deleted = true;
            string msg = string.Empty;
            StudentModel origin = null;
            if (_context.Students.Any(x => x.Id == id))
            {
                is_exist = true;
                origin = (StudentModel)_context.Students.First(x => x.Id == id).Clone();
                _context.Students.Remove(_context.Students.First(x => x.Id == id));
                try
                {
                    _context.SaveChanges();
                }
                catch (Exception ex)
                {
                    msg = ex.ToString();
                    is_deleted = false;
                }
            }

            bool is_error = false;

            if (!is_exist)
            {
                is_error = true;
                msg = "Student with such id didn't exist!";
            }
            else if (!is_deleted)
            {
                is_error = true;
            }

            List<LinkModel> links = null;
            if (!is_error)
            {
                links = new List<LinkModel>();
                string path = $@"{Request.RequestUri.Scheme}://{Request.RequestUri.Authority}{Request.RequestUri.LocalPath}";
                links.Add(new LinkModel
                {
                    Action = $"Back to List",
                    Method = "GET",
                    Url = $"Test",
                });
            }

            _ = Request.Properties.TryGetValue("formatter", out object value);
            (string, MediaTypeFormatter) type = ((string, MediaTypeFormatter))value;

            return new HttpResponseMessage()
            {
                Content = new ObjectContent<ResponseModel<StudentModel>>(
                    new ResponseModel<StudentModel>()
                    {
                        Object = !is_error ? origin : null,
                        Links = links,
                        Error = is_error ?
                        new ErrorModel
                        {
                            Message = msg
                        } : null
                    },
                    type.Item2,
                    type.Item1
                )
            };
        }
    }
}
