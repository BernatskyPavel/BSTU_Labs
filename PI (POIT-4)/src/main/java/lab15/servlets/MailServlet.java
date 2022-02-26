package lab15.servlets;

import java.io.IOException;

import jakarta.annotation.Resource;
import jakarta.mail.MessagingException;
import jakarta.mail.Session;
import jakarta.mail.Store;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

public class MailServlet extends HttpServlet {

	/**
	 * 
	 */
	private static final long serialVersionUID = -3164454675228713536L;

	@Resource(mappedName = "java:jboss/mail/Lab15Box1")
	private Session mailSession;

	@Resource(mappedName = "java:jboss/mail/Lab15Box2")
	private Session mailSession2;

	public MailServlet() {
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
		print(":doPost");
		String box = req.getParameter("mail");
		if (box == null || box.isBlank()) {
			resp.getWriter().write("Error: Wrong Mail value. Value can not be NULL/EMPTY!");
			return;
		}
		switch (box.toLowerCase()) {
			case "lab15box1":
				try {
					Store store = mailSession.getStore("pop3");
					store.connect();
					getServletContext().setAttribute("folder", store.getFolder("INBOX"));
					resp.sendRedirect("./mail.jsp");
				} catch (MessagingException e) {
					e.printStackTrace();
				}
				break;
			case "lab15box2":
				break;
			default:
				resp.getWriter().write("Error: Such Box does not exist!");
				break;
		}
	}

	@Override
	protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		print(":doPost");
		String box = req.getParameter("mail");
		if (box == null || box.isBlank()) {
			resp.getWriter().write("Error: Wrong Mail value. Value can not be NULL/EMPTY!");
			return;
		}

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
