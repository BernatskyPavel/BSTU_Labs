package lab03.servlets;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.ResponseHandler;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClients;
import org.apache.http.message.BasicNameValuePair;
import org.apache.http.util.EntityUtils;

import jakarta.servlet.ServletConfig;
import jakarta.servlet.ServletException;
import jakarta.servlet.ServletRequest;
import jakarta.servlet.ServletResponse;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.ws.rs.HttpMethod;

public class Sss extends HttpServlet {

	/**
	 * 
	 */
	private static final long serialVersionUID = 4685712704265329658L;
	private static final String WRONG_PROTOCOL = "Not Supported Protocol";

	@Override
	public void init(ServletConfig config) throws ServletException {
		super.init(config);
		print(":init");
	}

	@Override
	public void service(ServletRequest req, ServletResponse res) throws ServletException, IOException {
		String protocol = req.getProtocol();
		String method = "";
		switch (protocol) {
			case "HTTP/1.1":
			case "HTTP/2.0":
				method = ((HttpServletRequest) req).getMethod();
				break;
			default:
				method = WRONG_PROTOCOL;
				break;
		}
		switch (method) {
			case HttpMethod.GET:
				doGet((HttpServletRequest) req, (HttpServletResponse) res);
				break;
			case HttpMethod.POST:
				String mode = req.getParameter("mode");
				if (mode == null) {
					res.getWriter().write("No mode was selected!");
					return;
				}
				switch (mode.toLowerCase()) {
					case "forward":
						req.getRequestDispatcher("./GoGgg").forward(req, res);
						break;
					case "redirect":
						((HttpServletResponse) res).sendRedirect("./GoGgg");
						break;
				}
				print(":service:doPost");
				break;
			case WRONG_PROTOCOL:
				res.getWriter().write(WRONG_PROTOCOL);
				break;
			default:
				res.getWriter().write("Method Not Supported");
				break;
		}
		print(":service");
	}

	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		String button = req.getParameter("button");
		if (button == null) {
			resp.getWriter().write("No button was clicked!");
			return;
		}
		String mode = null;
		switch (button.toLowerCase()) {
			case "html method":
				mode = req.getParameter("mode");
				if (mode == null) {
					resp.getWriter().write("No mode was selected!");
					return;
				}
				switch (mode.toLowerCase()) {
					case "forward":
						req.getRequestDispatcher("./forward.xhtml").forward(req, resp);
						break;
					case "redirect":
						resp.sendRedirect("./forward.xhtml");
						break;
				}
				break;
			case "get method":
			case "dget method":
				resp.getWriter().append("This part of response is from Sss3 servlet.\n");
				mode = req.getParameter("mode");
				if (mode == null) {
					resp.getWriter().write("No mode was selected!");
					return;
				}
				switch (mode.toLowerCase()) {
					case "forward":
						req.getRequestDispatcher("./GoGgg").forward(req, resp);
						break;
					case "redirect":
						resp.sendRedirect("./GoGgg" + "?" + req.getQueryString());
						break;
				}
				break;
			case "internal method":
				CloseableHttpClient httpclient = HttpClients.createDefault();
				try {
					print(":doGet:internal");
					HttpGet httpGet = new HttpGet(req.getScheme() + "://" + req.getServerName() + ":"
							+ req.getServerPort()
							+ "/IPLabs-0.0.1-SNAPSHOT/Lab03/GoGgg?internal-firstname=" + req.getParameter("firstname")
							+ "internal-lastname=" + req.getParameter("lastname"));
					ResponseHandler<String> responseHandler = new ResponseHandler<String>() {
						@Override
						public String handleResponse(final HttpResponse response)
								throws ClientProtocolException, IOException {
							int status = response.getStatusLine().getStatusCode();
							if (status >= 200 && status < 300) {
								HttpEntity entity = response.getEntity();
								return entity != null ? EntityUtils.toString(entity) : null;
							} else {
								throw new ClientProtocolException("Unexpected response status: " + status);
							}
						}
					};
					String responseBody = httpclient.execute(httpGet, responseHandler);
					resp.getWriter().write(responseBody);
				} finally {
					httpclient.close();
				}
				break;
			case "internal method 2":
				CloseableHttpClient httpclient2 = HttpClients.createDefault();
				try {
					print(":doGet:internal");
					HttpPost httpPost = new HttpPost(req.getScheme() + "://" + req.getServerName() + ":"
							+ req.getServerPort() + "/IPLabs-0.0.1-SNAPSHOT/Lab03/GoGgg");
					List<NameValuePair> lnvp = new ArrayList<NameValuePair>();
					lnvp.add(new BasicNameValuePair("internal-firstname", req.getParameter("firstname")));
					lnvp.add(new BasicNameValuePair("internal-lastname", req.getParameter("lastname")));
					httpPost.setEntity(new UrlEncodedFormEntity(lnvp));

					ResponseHandler<String> responseHandler = new ResponseHandler<String>() {

						@Override
						public String handleResponse(final HttpResponse response)
								throws ClientProtocolException, IOException {
							int status = response.getStatusLine().getStatusCode();
							if (status >= 200 && status < 300) {
								HttpEntity entity = response.getEntity();
								return entity != null ? EntityUtils.toString(entity) : null;
							} else {
								throw new ClientProtocolException("Unexpected response status: " + status);
							}
						}
					};
					String responseBody = httpclient2.execute(httpPost, responseHandler);
					resp.getWriter().write(responseBody);
				} finally {
					httpclient2.close();
				}

				break;
			default:
				break;
		}
		print(":doGet");
	}

	@Override
	public void destroy() {
		super.destroy();
		print(":destroy");
	}

	private void print(String msg) {
		System.out.println(this.getClass().getName() + msg);
	}

}
