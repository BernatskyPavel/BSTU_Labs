import { serve } from "https://deno.land/std@0.127.0/http/server.ts";

async function handle(req: Request): Promise<Response> {
  const url: URL = new URL(req.url);

  switch (url.pathname) {
    case "/fact": {
      if (url.searchParams.has("k")) {
        const k = <string>url.searchParams.get("k");
        const ik = Number.parseInt(k);
        return new Response(`{"k":${ik}, "fact": ${fact(ik)}}`, {
          headers: {
            "Content-Type": "application/json; charset=utf-8",
          },
        });
      } else {
        return new Response("Missing parameter k!", {
          status: 404,
          headers: {
            "Content-Type": "plain/text; charset=utf-8",
          },
        });
      }
    }
    case "/":
      const encoder = new TextEncoder();
      const file = await Deno.readTextFile("index.xhtml");
      return new Response(encoder.encode(file), {
        headers: {
          "content-type": "text/html; charset=utf-8",
        },
      });
    default: {
      return new Response(null, {
        status: 404,
      });
    }
  }

  return new Response();
}

function fact(num: number): number {
  return 0;
}

serve(handle, { port: 5000 });
