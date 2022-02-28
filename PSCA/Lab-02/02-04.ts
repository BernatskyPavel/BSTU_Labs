import { serve } from "https://deno.land/std@0.127.0/http/server.ts";

async function handler(req: Request): Promise<Response> {
  const url: URL = new URL(req.url);

  switch (url.pathname) {
    case "/xmlhttprequest": {
      const encoder = new TextEncoder();
      const file = await Deno.readTextFile("xmlhttprequest.xhtml");
      return new Response(encoder.encode(file), {
        headers: {
          "content-type": "text/html; charset=utf-8",
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
