package lab06.servlets;

import java.io.IOException;

import jakarta.servlet.Servlet;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

public class Sss extends lab02.servlets.Sss implements Servlet {

	/**
	 * 
	 */
	private static final long serialVersionUID = -1159204038092254136L;

	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		super.print(":doGet");
		String urlparam = req.getParameter("urln");
		if (urlparam == null) {
			resp.getWriter().write("Error: Wrong urln value. Value can not be NULL!");
			return;
		}
		switch (urlparam) {
		case "1":
		case "2":
			resp.sendRedirect(getServletContext().getInitParameter("URL" + urlparam));
			break;
		default:
			resp.getWriter().write("Error: Wrong urln value. Value can be only '1' or '2'!");
			break;
		}
	}

	@Override
	protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		super.print(":doPost");
		resp.getWriter().write("Error: Method is not available!");
	}
}
