using Lab_08.Helpers;
using Lab_08.Models;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Reflection;
using System.Web;
using System.Web.Http;
using System.Web.SessionState;

namespace Lab_08.Controllers {
    [RoutePrefix("jsonrpc")]
    public class JsonRPCController: ApiController, IRequiresSessionState {
        [Route("")]
        public HttpResponseMessage Post([FromBody] JsonRPCRequest request) {

            JsonRPCResponse response = ProcessJsonRPCRequest(request);

            if (response != null && request != null)
                response.Id = request.Id;
            return response.Id != null ? new HttpResponseMessage() {
                Content = new ObjectContent<JsonRPCResponse>(
                    response,
                    GlobalConfiguration.Configuration.Formatters.JsonFormatter,
                    "application/json"
                )
            } : new HttpResponseMessage(HttpStatusCode.NoContent);
        }

        [Route("pack")]
        public HttpResponseMessage Post([FromBody] List<JsonRPCRequest> requests) {

            JsonRPCResponse[] responses = new JsonRPCResponse[requests.Count];

            int i = 0;

            foreach (JsonRPCRequest request in requests) {
                JsonRPCResponse response = ProcessJsonRPCRequest(request);
                if (response != null) {
                    if (request != null)
                        response.Id = request.Id;
                    responses[i++] = response.Id != null ? response : null;
                }

            }

            return new HttpResponseMessage() {
                Content = new ObjectContent<JsonRPCResponse[]>(
                    responses.Where(resp => resp != null).ToArray(),
                    GlobalConfiguration.Configuration.Formatters.JsonFormatter,
                    "application/json"
                )
            };
        }

        private JsonRPCResponse ProcessJsonRPCRequest(JsonRPCRequest request) {
            JsonRPCResponse response = new JsonRPCResponse();
            response.Jsonrpc = "2.0";

            if (SerializerErrorsHolder.Errors.Count != 0) {
                if (request != null && request.Id != null) {
                    response.Id = request.Id;
                }
                else {
                    response.Id = $"error-{SerializerErrorsHolder.Errors.Count}";
                }
                response.Error = new JsonRPCError(JsonRPCErrorCodes.ParseError) {
                    Data = SerializerErrorsHolder.Errors.Dequeue()
                };
            }
            else {
                object temp = HttpContext.Current.Session[JRService._exit];

                if (temp != null && (bool)temp && request.Method != "Reload") {
                    return null;
                }

                MethodInfo method = typeof(JRService).GetMethod(request.Method);
                if (method == null) {
                    response.Error = new JsonRPCError(JsonRPCErrorCodes.MethodNotFound);
                    return response;
                }

                ParameterInfo[] parameters = method.GetParameters();

                if (parameters != null) {
                    object[] args = new object[parameters.Length];

                    if (request.Params.GetType() == typeof(JArray)) {
                        JArray array = (JArray)request.Params;
                        if (array.Count < parameters.Length) {
                            response.Error = new JsonRPCError(JsonRPCErrorCodes.InvalidParams) {
                                Data = "Number of parameters that passed is not enough."
                            };
                            return response;
                        }

                        args = array.Select(el => TransformJToken(el)).ToArray();
                    }
                    else if (request.Params.GetType() == typeof(JObject)) {
                        bool is_all_args = parameters.All(arg => {
                            return ((JObject)request.Params).ContainsKey(arg.Name);
                        });
                        if (!is_all_args) {
                            response.Error = new JsonRPCError(JsonRPCErrorCodes.InvalidParams) {
                                Data = $@"{parameters
                                    .Where(arg => { return !((JObject)request.Params).ContainsKey(arg.Name); })
                                    .Select(arg => { return arg.Name; })
                                    .Aggregate((arg1, arg2) => { return $"{arg1}, {arg2}"; })} missing."
                            };
                            return response;
                        }
                        int i = 0;
                        foreach (ParameterInfo arg in parameters) {
                            args[i++] = TransformJToken(((JObject)request.Params)[arg.Name]);
                        }
                    }
                    else {
                        response.Error = new JsonRPCError(JsonRPCErrorCodes.ParseError) {
                            Data = "Parameters can be passed only as Array or Object."
                        };
                        return response;
                    }

                    object result = null;
                    try {
                        JRService service = new JRService(HttpContext.Current.Session);
                        result = method.Invoke(service, args);
                    }
                    catch (Exception ex) {
                        if (ex is TargetParameterCountException || ex is ArgumentException) {
                            response.Error = new JsonRPCError(JsonRPCErrorCodes.InvalidParams) {
                                Data = ex.Message
                            };
                        }
                        else {
                            response.Error = new JsonRPCError(JsonRPCErrorCodes.InternalError) {
                                Data = ex.InnerException.Message
                            };
                        }
                        return response;
                    }
                    response.Result = result;
                }
            }
            return response;
        }

        private object TransformJToken(JToken value) {
            switch (value.Type) {
                case JTokenType.String:
                    return value.Value<string>();
                case JTokenType.None:
                    return null;
                case JTokenType.Object:
                    return value.Value<object>();
                case JTokenType.Array:
                    return value.Value<object[]>();
                case JTokenType.Constructor:
                    return null;
                case JTokenType.Property:
                    return null;
                case JTokenType.Comment:
                    return null;
                case JTokenType.Integer:
                    return value.Value<int>();
                case JTokenType.Float:
                    return value.Value<float>();
                case JTokenType.Boolean:
                    return value.Value<bool>();
                case JTokenType.Null:
                    return null;
                case JTokenType.Undefined:
                    return null;
                case JTokenType.Date:
                    return value.Value<DateTime>();
                case JTokenType.Raw:
                    return null;
                case JTokenType.Bytes:
                    return value.Value<byte[]>();
                case JTokenType.Guid:
                    return value.Value<Guid>();
                case JTokenType.Uri:
                    return value.Value<string>();
                case JTokenType.TimeSpan:
                    return value.Value<TimeSpan>();
            }
            return null;
        }
    }
}
