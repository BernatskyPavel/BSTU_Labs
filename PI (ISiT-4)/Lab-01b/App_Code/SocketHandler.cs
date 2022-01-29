using System;
using System.Net.WebSockets;
using System.Threading;
using System.Threading.Tasks;
using System.Web;
using System.Web.WebSockets;

namespace Lab_01b.App_Code {
    public class SocketHandler: IHttpHandler {
        WebSocket socket;

        #region IHttpHandler Members

        public bool IsReusable {
            get {
                return false;
            }
        }

        public void ProcessRequest(HttpContext context) {
            if (context.IsWebSocketRequest) {
                context.AcceptWebSocketRequest(WebSocketRequest);
            }
        }

        #endregion

        #region SocketHandler Members

        private async Task WebSocketRequest(AspNetWebSocketContext ws_context) {
            socket = ws_context.WebSocket;
            string s = await Recieve();
            await Send(s);
            while (socket.State == WebSocketState.Open) {
                Thread.Sleep(2000);
                await Send($"[{DateTime.Now.TimeOfDay.ToString().Split('.')[0]}]");
            }
        }

        private void Sleep(int v) {
            throw new NotImplementedException();
        }

        private async Task<string> Recieve() {
            ArraySegment<byte> buffer = new ArraySegment<byte>(new byte[512]);
            WebSocketReceiveResult result = await this.socket.ReceiveAsync(buffer, CancellationToken.None);
            string rc = System.Text.Encoding.UTF8.GetString(buffer.Array, 0, result.Count);
            return rc;
        }

        private async Task Send(string s) {
            ArraySegment<byte> send_buffer = new ArraySegment<byte>(System.Text.Encoding.UTF8.GetBytes("Ответ: " + s));
            await this.socket.SendAsync(send_buffer,
                                        WebSocketMessageType.Text,
                                        true,
                                        CancellationToken.None);
        }

        #endregion
    }
}
