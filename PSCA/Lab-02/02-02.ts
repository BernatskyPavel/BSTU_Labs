import { serve } from "https://deno.land/std@0.127.0/http/server.ts";

async function handler(req: Request): Promise<Response> {
  const url: URL = new URL(req.url);

  switch (url.pathname) {
    case "/png": {
      const file = await Deno.readFile("pic.png");
      return new Response(file, {
        headers: {
          "Content-Type": "img/png; charset=utf-8",
          "Content-Disposition": "inline",
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
