package lab05.servlets;

import java.io.IOException;

import jakarta.servlet.Servlet;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

public class Ttt extends HttpServlet implements Servlet {

	/**
	 * 
	 */
	private static final long serialVersionUID = 4953980608381697312L;

	public Ttt() {
		super();
		print(":constructor");
	}

	@Override
	public void init() throws ServletException {
		super.init();
		print(":init");
	}

	@Override
	protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		print(":doPost");
		resp.getWriter().write("Surname:" + req.getParameter("bpv-surname") + "\nLastname:"
				+ req.getParameter("bpv-lastname") + "\nSex:" + req.getParameter("bpv-sex"));
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
