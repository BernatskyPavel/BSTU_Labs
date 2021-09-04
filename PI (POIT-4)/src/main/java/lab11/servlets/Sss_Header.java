package lab11.servlets;

import java.io.IOException;

import org.apache.http.HttpStatus;

import jakarta.servlet.Servlet;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

public class Sss_Header extends HttpServlet implements Servlet {

	/**
	 * 
	 */
	private static final long serialVersionUID = -3783778995348685951L;

	public Sss_Header() {
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
		try {
			Thread.sleep(10000);
		} catch (InterruptedException e) {
			System.err.println(e.getMessage());
			return;
		}
		String xvalue = req.getHeader("Value-X");
		String yvalue = req.getHeader("Value-Y");
		if (xvalue == null || yvalue == null) {
			resp.sendError(HttpStatus.SC_EXPECTATION_FAILED, "Headers can't be null!");
			return;
		}
		if (xvalue.isBlank() || yvalue.isBlank()) {
			resp.sendError(HttpStatus.SC_EXPECTATION_FAILED, "Headers can't be empty!");
			return;
		}
		xvalue = xvalue.strip();
		yvalue = yvalue.strip();
		if (!xvalue.matches("-{0,1}\\d+") || !yvalue.matches("-{0,1}\\d+")) {
			resp.sendError(HttpStatus.SC_EXPECTATION_FAILED, "Headers must be integers!");
			return;
		}
		int x, y;
		x = Integer.parseInt(xvalue);
		y = Integer.parseInt(yvalue);
		
		resp.setHeader("Value-Z", Integer.toString(x + y));
		
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
