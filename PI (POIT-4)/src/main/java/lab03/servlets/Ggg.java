package lab03.servlets;

import java.io.IOException;
import java.io.PrintWriter;

import jakarta.servlet.ServletConfig;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

public class Ggg extends HttpServlet {

	/**
	 * 
	 */
	private static final long serialVersionUID = 2319883339895602338L;

	@Override
	public void init(ServletConfig config) throws ServletException {
		super.init(config);
		print(":init");
	}

	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		String button = req.getParameter("button");
		if (button == null) {
			button = "default";
		}
		if (button.toLowerCase().equals("dget method")) {
			String mode = req.getParameter("mode");
			if (mode == null) {
				resp.getWriter().write("No mode was selected!");
				return;
			}
			switch (mode.toLowerCase()) {
				case "forward":
					req.getRequestDispatcher("./forward.xhtml").forward(req, resp);
					break;
				case "redirect":
					resp.sendRedirect("./forward.xhtml");
					break;
			}
		} else {
			PrintWriter pw = resp.getWriter();
			pw.write("Hello from Ggg3(Get)!\n");
			req.getParameterMap().forEach((x, y) -> pw.write(x + ":" + y[0] + "\n"));
		}
		print(":doGet");
	}

	@Override
	protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		PrintWriter pw = resp.getWriter();
		pw.write("Hello from Ggg3(Post)!\n");
		req.getParameterMap().forEach((x, y) -> pw.write(x + ":" + y[0] + "\n"));
		print(":doPost");
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
