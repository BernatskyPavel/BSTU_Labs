package lab08.servlets;

import java.io.IOException;

import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

public class Bbb extends lab02.servlets.Sss {

	/**
	 * 
	 */
	private static final long serialVersionUID = -6922827279636454465L;

	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		super.print(":doGet");
		resp.getWriter().write("Error: Method is not available!");
	}

	@Override
	protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		super.print(":doPost");
		StringBuilder responseText = new StringBuilder();
		responseText.append("-----Params-----\n");
		var Iterator = req.getParameterNames().asIterator();
		while (Iterator.hasNext()) {
			String param = Iterator.next();
			responseText.append(
					param + ": " + req.getParameter(param) + '\n');
		}
		Iterator = req.getHeaderNames().asIterator();
		responseText.append("-----Headers-----\n");
		while (Iterator.hasNext()) {
			String header = Iterator.next();
			responseText.append(header + ": " + req.getHeader(header) + '\n');
		}
		resp.setHeader("bpv-response-1", "-_-");
		resp.setHeader("bpv-response-2", "X_X");
		resp.getWriter().write(responseText.toString());
	}
}
