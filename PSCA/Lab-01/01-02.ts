import { serve } from "https://deno.land/std@0.127.0/http/server.ts";

function handler(req: Request): Response {
    return new Response("<h1>Hello, World!</h1>", {
        headers: {
            "content-type": "text/html; charset=utf-8",
        },
    });
}

serve(handler)