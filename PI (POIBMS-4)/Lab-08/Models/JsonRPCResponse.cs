using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace Lab_08.Models {
    [JsonObject]
    public class JsonRPCResponse {
        [JsonProperty(PropertyName = "jsonrpc", Required = Required.Always)]
        public string Jsonrpc {
            get;set;
        }
        [JsonProperty(PropertyName = "id", Required = Required.Always)]
        public string Id {
            get;set;
        }

        [JsonProperty(PropertyName = "error", Required = Required.AllowNull)]
        public JsonRPCError Error {
            get;set;
        }

        [JsonProperty(PropertyName = "result", Required = Required.AllowNull)]
        public dynamic Result {
            get;set;
        }
    }
}