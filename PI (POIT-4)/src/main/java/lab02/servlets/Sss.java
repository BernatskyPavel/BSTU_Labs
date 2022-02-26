package lab02.servlets;

import java.io.IOException;

import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

public class Sss extends HttpServlet {
	/**
	 * 
	 */
	private static final long serialVersionUID = 5679263330393149451L;

	public Sss() {
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
		resp.getWriter().write(this.getClass().getName() + ":service" +
				"\nmethod:" + req.getMethod() +
				"\nserver-name:" + req.getServerName() +
				"\nIP:" + req.getLocalAddr() +
				"\nfirstname:" + req.getParameter("firstname") +
				"\nlastname:" + req.getParameter("lastname") +
				"\nURL:" + req.getRequestURL() + "?" + req.getQueryString());
	}

	@Override
	protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		print(":doPost");
		resp.getWriter().write(this.getClass().getName() + ":service" +
				"\nmethod:" + req.getMethod() +
				"\nserver-name:" + req.getServerName() +
				"\nIP:" + req.getLocalAddr() +
				"\nfirstname:" + req.getParameter("firstname") +
				"\nlastname:" + req.getParameter("lastname"));
	}

	@Override
	public void destroy() {
		super.destroy();
		print(":destroy");
	}

	protected void print(String msg) {
		System.out.println(this.getClass().getName() + msg);
	}

}
