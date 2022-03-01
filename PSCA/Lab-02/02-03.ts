import { serve } from "https://deno.land/std@0.127.0/http/server.ts";

async function handler(req: Request): Promise<Response> {
  const url: URL = new URL(req.url);

  switch (url.pathname) {
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
