using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using Newtonsoft.Json.Serialization;
using Newtonsoft.Json;
using System.Runtime.Serialization;

namespace Lab_08.Models {
    [JsonObject(ItemNullValueHandling = NullValueHandling.Ignore)]
    public class JsonRPCRequest {
        [JsonProperty(PropertyName = "jsonrpc", Required = Required.Always)]
        public string Jsonrpc {
            get; set;
        }
        [JsonProperty(PropertyName = "id", Required = Required.AllowNull)]
        public string Id {
            get; set;
        }
        [JsonProperty(PropertyName = "method", Required = Required.Always)]
        public string Method {
            get; set;
        }
        [JsonProperty(PropertyName = "params", Required = Required.AllowNull)]
        public dynamic Params {
            get; set;
        }
    }

    [JsonArray]
    public class JsonRPCRequests {
        public JsonRPCRequest[] Requests {
            get; set;
        }
    }
}