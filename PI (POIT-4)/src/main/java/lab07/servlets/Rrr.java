package lab07.servlets;

import java.io.IOException;

import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import lab06.helpers.CBean;

public class Rrr extends HttpServlet {

	/**
	 * 
	 */
	private static final long serialVersionUID = -954784254121096373L;

	public Rrr() {
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
		resp.sendRedirect("./Rrr.jsp");
	}

	@Override
	protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		print(":doPost");
		String param1, param2, param3, paramBean;
		paramBean = req.getParameter("CBean");
		if (paramBean == null) {
			resp.getWriter().write("Error: Wrong CBean value. Value can not be NULL!");
			return;
		}
		param1 = req.getParameter("Value1");
		param2 = req.getParameter("Value2");
		param3 = req.getParameter("Value3");
		CBean newCBean = new CBean(param1, param2, param3);
		switch (paramBean.toLowerCase()) {
			case "new":
				req.setAttribute("CBean", newCBean);
				break;
			case "old":
				this.replace((CBean) req.getAttribute("CBean"), newCBean);
				break;
			default:
				resp.getWriter().write("Error: Wrong CBean value. Value can be only 'old' or 'new'!");
				break;
		}
		resp.sendRedirect("./Rrr.jsp");
	}

	@Override
	public void destroy() {
		super.destroy();
		print(":destroy");
	}

	private void print(String msg) {
		System.out.println(this.getClass().getName() + msg);
	}

	private void replace(CBean _old, CBean _new) {
		if (_old == null)
			return;
		if (_new.getValue1() != null && !_new.getValue1().isBlank())
			_old.setValue1(_new.getValue1());
		if (_new.getValue2() != null && !_new.getValue2().isBlank())
			_old.setValue2(_new.getValue2());
		if (_new.getValue3() != null && !_new.getValue3().isBlank())
			_old.setValue3(_new.getValue3());
	}
}
