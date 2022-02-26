package lab13.servlets;

import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.net.URLEncoder;

import jakarta.servlet.ServletException;
import jakarta.servlet.ServletOutputStream;
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
		String filename = req.getParameter("file");
		String dir = getServletContext().getInitParameter("Lab13Files");

		if (filename == null || filename.isBlank()) {
			resp.getWriter().write("Error: Wrong Filename value. Value can not be NULL/EMPTY!");
			return;
		}

		if (dir == null) {
			resp.getWriter().write("Error: Problems on server!");
			return;
		}
		File file = new File(dir + "/" + filename);
		if (!file.exists()) {
			resp.getWriter().write("Error: File do not exist!");
			return;
		}
		resp.setContentType("application/msword");
		resp.addHeader("Content-Disposition",
				"attachment; filename=" + URLEncoder.encode(file.getName(), "UTF-8"));
		resp.setContentLength((int) file.length());
		FileInputStream in = new FileInputStream(file);
		BufferedInputStream buff = new BufferedInputStream(in);
		ServletOutputStream out = resp.getOutputStream();
		int readBytes = 0;
		while ((readBytes = buff.read()) != -1) {
			out.write(readBytes);
		}
		buff.close();
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
