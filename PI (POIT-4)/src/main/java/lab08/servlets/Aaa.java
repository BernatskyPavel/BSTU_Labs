package lab08.servlets;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import org.apache.http.Header;
import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.BasicResponseHandler;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClients;
import org.apache.http.message.BasicNameValuePair;

import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

public class Aaa extends lab02.servlets.Sss {

	/**
	 * 
	 */
	private static final long serialVersionUID = -6000959014569477439L;

	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		super.print(":doGet");
		CloseableHttpClient httpclient = HttpClients.createDefault();
		try {
			HttpPost httpPost = new HttpPost(req.getScheme() + "://" + req.getServerName() + ":" + req.getServerPort()
					+ "/IPLabs-0.0.1-SNAPSHOT/Lab08/GoBbb");
			List<NameValuePair> params = new ArrayList<NameValuePair>();
			params.add(new BasicNameValuePair("bpv-param-1", "example-3"));
			params.add(new BasicNameValuePair("bpv-param-2", "example-1"));
			params.add(new BasicNameValuePair("bpv-param-3", "example-2"));
			httpPost.setEntity(new UrlEncodedFormEntity(params));
			httpPost.setHeader("bpv-header-1", "^_^");
			httpPost.setHeader("bpv-header-2", "O_O");
			httpPost.setHeader("bpv-header-3", "T_T");
			HttpResponse response = httpclient.execute(httpPost);
			String responseBody = new BasicResponseHandler().handleResponse(response);
			responseBody += "\n-----Response Headers-----\n";
			var headers = response.getAllHeaders();
			for (Header header : headers) {
				responseBody += header.getName() + ": " + header.getValue() + "\n";
			}
			resp.getWriter().write(responseBody);
		} finally {
			httpclient.close();
		}
	}

	@Override
	protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		super.print(":doPost");
		resp.getWriter().write("Error: Method is not available!");
	}
}
