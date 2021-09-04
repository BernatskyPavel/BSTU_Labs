package lab12.servlets;

import java.io.IOException;

import jakarta.servlet.Servlet;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

public class Sss extends HttpServlet implements Servlet {
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
		resp.getWriter().write("Hello From Sss!");
	}
	
	@Override
	public void destroy() {
		super.destroy();
		print(":destroy");
	}

	protected void print(String msg) {
		System.out.println(this.getClass().getName()+msg);
	}
	

}
