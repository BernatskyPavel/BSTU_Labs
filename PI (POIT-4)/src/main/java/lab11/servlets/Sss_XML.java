package lab11.servlets;

import java.io.IOException;

import org.apache.http.HttpStatus;

import jakarta.servlet.Servlet;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

public class Sss_XML extends HttpServlet implements Servlet {

	/**
	 * 
	 */
	private static final long serialVersionUID = -1671828546035747693L;

	public Sss_XML() {
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
			Thread.sleep(5000);
		} catch (InterruptedException e) {
			System.err.println(e.getMessage());
			return;
		}
		String nvalue = req.getHeader("XRand-N");
		System.out.println("NValue:" + nvalue);
		if (nvalue == null) {
			resp.sendError(HttpStatus.SC_EXPECTATION_FAILED, "Header can't be null!");
			return;
		}
		if (nvalue.isBlank()) {
			resp.sendError(HttpStatus.SC_EXPECTATION_FAILED, "Header can't be empty!");
			return;
		}
		nvalue = nvalue.strip();
		if (!nvalue.matches("\\d+")) {
			resp.sendError(HttpStatus.SC_EXPECTATION_FAILED, "Headers must be positive integer!");
			return;
		}
		int n;
		n = Integer.parseInt(nvalue);
		double x = 5.0 * (1 + (Math.random() / Math.nextDown(1.0)));
		int rand = 0;
		String xml = "<root>";
		System.out.println("X:" + x);
		for (int i = 0; i < x; i++) {
			rand = (int) (n * (2 * (Math.random() / Math.nextDown(1.0)) - 1.0));
			xml = xml + "<rand>" + rand + "</rand>";
		}
		xml = xml + "</root>";
		resp.setContentType("text/xml");
		resp.getWriter().write(xml);
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
