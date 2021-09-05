package labX.servlets;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;

import org.jboss.resteasy.util.HttpResponseCodes;

import jakarta.servlet.Servlet;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.MultipartConfig;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.Part;

@MultipartConfig
public class WebDAV extends HttpServlet implements Servlet {

	/**
	 * 
	 */
	private static final long serialVersionUID = -4367009879520942915L;

	@Override
	public void init() throws ServletException {
		print(":init");
		super.init();
	}

	public WebDAV() {
		print(":construct");
	}

	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		// TODO Auto-generated method stub
		super.doGet(req, resp);
	}

	@Override
	protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		if (req.getContentType().startsWith("multipart/form-data")) {
			if (req.getParameter("op") == null) {
				resp.sendError(HttpResponseCodes.SC_BAD_REQUEST, "Method is not supported!");
			}
			switch (req.getParameter("op").toLowerCase()) {
			case "get":
				break;
			case "put":
				break;
			case "copy":
				break;
			case "mkcol":
				break;
			case "delete":
				break;
			case "move":
				break;
			default:
				resp.sendError(HttpResponseCodes.SC_BAD_REQUEST, "Method is not supported!");
				break;
			}

			ArrayList<Part> parts = new ArrayList<Part>();
			parts.addAll(req.getParts());
			String result = null;
			for (Part part : parts) {
				if (part.getName().equals("DAV-file")) {
					result = "<h3>" + part.getSubmittedFileName() + "</h3><br/>";
					Files.write(Path.of("E:", "Uploads", part.getSubmittedFileName()),
							part.getInputStream().readAllBytes());
				}
			}

			resp.getWriter().write(result);
		} else {
			resp.getWriter().write("Not a multipart!");
		}
		// resp.sendRedirect("/IPLabs/index.xhtml");
	}

	@Override
	public void destroy() {
		print(":destroy");
		super.destroy();
	}

	private void print(String msg) {
		System.out.println(this.getClass().getName() + msg);
	}

}
