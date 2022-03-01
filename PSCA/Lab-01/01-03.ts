import { serve } from "https://deno.land/std@0.127.0/http/server.ts";

async function handler(req: Request): Promise<Response> {

    const url: URL = new URL(req.url)

    let headers_str: String = "";

    for(const key of req.headers.keys()) {
        headers_str += `${key}: ${req.headers.get(key)}<br/>\n`
    }

    return new Response(
        `<h1>Hello, World!</h1>
<p>Method: ${req.method}</p>
<p>URL: ${url.protocol}//${url.hostname}:${url.port}${url.pathname}</p>
<p>Parameters: ${url.searchParams.toString()}</p>
<p>Headers:<br/>
${headers_str}</p>
<p>Body: ${await req.text()}</p>`, {
        headers: {
            "content-type": "text/html; charset=utf-8",
        },
    });
}

serve(handler)