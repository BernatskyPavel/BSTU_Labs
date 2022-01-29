using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace Lab_08.Models {
    [JsonObject]
    public class JsonRPCError {
        [JsonProperty(PropertyName = "code", Required = Required.Always)]
        public short Code {
            get; set;
        }
        [JsonProperty(PropertyName = "message", Required = Required.Always)]
        public string Message {
            get; set;
        }
        [JsonProperty(PropertyName = "data", Required = Required.AllowNull)]
        public dynamic Data {
            get; set;
        }

        public JsonRPCError() {
        }

        public JsonRPCError(short code, string message) {
            this.Code = code;
            this.Message = message;
        }

        public JsonRPCError(JsonRPCErrorCodes code) {
            switch (code) {
                case JsonRPCErrorCodes.ParseError:
                    this.Code = -32700;
                    this.Message = "Invalid JSON was recieved by the server";
                    break;
                case JsonRPCErrorCodes.InvalidRequest:
                    this.Code = -32600;
                    this.Message = "The JSON sent is not a valid Request object";
                    break;
                case JsonRPCErrorCodes.MethodNotFound:
                    this.Code = -32601;
                    this.Message = "The method does not exist / is not available";
                    break;
                case JsonRPCErrorCodes.InvalidParams:
                    this.Code = -32602;
                    this.Message = "Invalid method parameter(s)";
                    break;
                case JsonRPCErrorCodes.InternalError:
                    this.Code = -32603;
                    this.Message = "Internal JSON-RPC error";
                    break;
            }
        }
    }

    public enum JsonRPCErrorCodes {
        ParseError,
        InvalidRequest,
        MethodNotFound,
        InvalidParams,
        InternalError
    }
}