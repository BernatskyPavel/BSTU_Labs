package lab04.servlets;

import java.io.IOException;

import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

public class Afternoon extends HttpServlet {

	/**
	 * 
	 */
	private static final long serialVersionUID = 7024593577296819897L;

	public Afternoon() {
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
		resp.getWriter().write("<h1>Servlet:Good Afternoon!</h1>");
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
