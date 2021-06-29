using System;
using System.Net.WebSockets;
using System.Threading;
using System.Threading.Tasks;
using System.Web;
using System.Web.WebSockets;

namespace Lab_01b.App_Code
{
    public class SocketHandler : IHttpHandler
    {

        WebSocket socket;

        /// <summary>
        /// You will need to configure this handler in the Web.config file of your 
        /// web and register it with IIS before being able to use it. For more information
        /// see the following link: https://go.microsoft.com/?linkid=8101007
        /// </summary>
        #region IHttpHandler Members

        public bool IsReusable
        {
            // Return false in case your Managed Handler cannot be reused for another request.
            // Usually this would be false in case you have some state information preserved per request.
            get { return false; }
        }

        public void ProcessRequest(HttpContext context)
        {
            //write your handler implementation here.
            if (context.IsWebSocketRequest)
            {
                context.AcceptWebSocketRequest(WebSocketRequest);
            }
        }

        #endregion

        #region SocketHandler Members

        private async Task WebSocketRequest(AspNetWebSocketContext ws_context)
        {
            socket = ws_context.WebSocket;
            string s = await Recieve();
            await Send(s);
            int i = 0;
            while (socket.State == WebSocketState.Open)
            {
                Thread.Sleep(2000);
                await Send("[" + (i++).ToString() + "]");
            }
        }

        private void Sleep(int v)
        {
            throw new NotImplementedException();
        }

        private async Task<string> Recieve()
        {
            string rc = string.Empty;
            ArraySegment<byte> buffer = new ArraySegment<byte>(new byte[512]);
            WebSocketReceiveResult result = await socket.ReceiveAsync(buffer, CancellationToken.None);
            rc = System.Text.Encoding.UTF8.GetString(buffer.Array, 0, result.Count);
            return rc;
        }

        private async Task Send(string s)
        {
            ArraySegment<byte> send_buffer = new ArraySegment<byte>(System.Text.Encoding.UTF8.GetBytes("Ответ: " + s));
            await socket.SendAsync(send_buffer, WebSocketMessageType.Text, true, CancellationToken.None);
        }

        #endregion
    }
}
