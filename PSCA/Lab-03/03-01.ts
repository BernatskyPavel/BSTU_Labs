import { serve } from "https://deno.land/std@0.127.0/http/server.ts";

var status = "norm";

async function handler(req: Request): Promise<Response> {
  const url: URL = new URL(req.url);

  switch (url.pathname) {
    case "/": {
      return new Response(`<h1>${status}</h1>`, {
        headers: {
          "content-type": "text/html; charset=utf-8",
        },
      });
    }
    case "/jquery-3.6.0.min.js": {
      const file = await Deno.readFile("jquery-3.6.0.min.js");
      return new Response(file, {
        headers: {
          "Content-Type": "application/javascript; charset=utf-8",
        },
      });
    }
    case "/api/name": {
      return new Response("Bernatsky Pavel Vladimirovich", {
        headers: {
          "Content-Type": "text/plain; charset=utf-8",
        },
      });
    }
    default: {
      return new Response(null, {
        status: 404,
      });
    }
  }
}

serve(handler, { port: 5000 });

const buf = new Uint8Array(1024);
const decoder = new TextDecoder();
const encoder = new TextEncoder();
while (true) {
  Deno.stdout.write(encoder.encode(`${status}->`));
  const len = <number>await Deno.stdin.read(buf);
  const cmd = decoder.decode(buf.subarray(0, len)).trim();
  switch (cmd) {
    case "norm":
    case "idle":
    case "test":
    case "stop":
      Deno.stdout.write(encoder.encode(`reg = ${status}--> ${cmd}\n`));
      status = cmd;
      break;
    case "exit":
      Deno.exit(0);
      break;
    default:
      Deno.stdout.write(encoder.encode(`${cmd}\n`));
      break;
  }
}
