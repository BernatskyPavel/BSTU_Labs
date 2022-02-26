package lab11.servlets;

import java.io.IOException;

import org.apache.http.HttpStatus;

import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

public class Sss_JSON extends HttpServlet {

	/**
	 * 
	 */
	private static final long serialVersionUID = 8878441799302091357L;

	public Sss_JSON() {
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
			Thread.sleep(1000);
		} catch (InterruptedException e) {
			System.err.println(e.getMessage());
			return;
		}
		String nvalue = req.getHeader("XRand-N");
		if (nvalue == null) {
			resp.sendError(HttpStatus.SC_EXPECTATION_FAILED, "Header can't be null/empty!");
			return;
		}
		if (nvalue.isBlank()) {
			resp.sendError(HttpStatus.SC_EXPECTATION_FAILED, "Header can't be null/empty!");
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
		String json = "{\n\"rands\" : [";
		System.out.println("X:" + x);
		for (int i = 0; i < x; i++) {
			rand = (int) (n * (2 * (Math.random() / Math.nextDown(1.0)) - 1.0));
			json = json + rand + ",";
		}
		json = json.substring(0, json.length() - 1);
		json = json + "]\n}";
		resp.setContentType("application/json");
		resp.getWriter().write(json);

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
