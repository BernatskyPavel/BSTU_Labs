package lab04.servlets;

import java.io.IOException;
import java.time.LocalTime;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.ResponseHandler;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClients;
import org.apache.http.util.EntityUtils;

import jakarta.servlet.Servlet;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

public class Jjj extends HttpServlet implements Servlet {

	/**
	 * 
	 */
	private static final long serialVersionUID = 8585427350276937953L;

	public Jjj() {
		super();
		print(":constructor");
	}

	@Override
	public void init() throws ServletException {
		super.init();
		print(":init");
	}

	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		print(":doGet");
		String param = req.getParameter("type");
		if (param == null) {
			resp.getWriter().write("Error:Type is null!");
			resp.flushBuffer();
			return;
		}
		int hour = LocalTime.now().getHour();
		CloseableHttpClient httpclient = HttpClients.createDefault();
		ResponseHandler<String> responseHandler = new ResponseHandler<String>() {
			@Override
			public String handleResponse(final HttpResponse response) throws ClientProtocolException, IOException {
				int status = response.getStatusLine().getStatusCode();
				if (status >= 200 && status < 300) {
					HttpEntity entity = response.getEntity();
					return entity != null ? EntityUtils.toString(entity) : null;
				} else {
					throw new ClientProtocolException("Unexpected response status: " + status);
				}
			}
		};
		String page = "";
		if (hour >= 0 && hour <= 5)
			page = "night.jsp";
		else if (hour >= 6 && hour <= 11)
			page = "morning.jsp";
		else if (hour >= 12 && hour <= 17)
			page = "afternoon.jsp";
		else
			page = "evening.jsp";
		switch (param.toLowerCase()) {
		case "simple":
			resp.sendRedirect("./" + page);
			break;
		case "get":
			try {
				HttpGet httpGet = new HttpGet(req.getScheme() + "://" + req.getServerName() + ":" + req.getServerPort()
						+ "/IPLabs-0.0.1-SNAPSHOT/Lab04/" + page);
				String responseBody = httpclient.execute(httpGet, responseHandler);
				resp.getWriter().write(responseBody);
			} finally {
				httpclient.close();
			}
			break;
		case "post":
			try {
				HttpPost httpPost = new HttpPost(req.getScheme() + "://" + req.getServerName() + ":"
						+ req.getServerPort() + "/IPLabs-0.0.1-SNAPSHOT/Lab04/" + page);
				String responseBody = httpclient.execute(httpPost, responseHandler);
				resp.getWriter().write(responseBody);
			} finally {
				httpclient.close();
			}
			break;
		}
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
