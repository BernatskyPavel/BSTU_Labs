package lab09.filters;

import java.io.IOException;

import jakarta.servlet.FilterChain;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpFilter;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

public class F3 extends HttpFilter {

	/**
	 * 
	 */
	private static final long serialVersionUID = 3977039907658021277L;

	@Override
	public void init() throws ServletException {
		super.init();
		print(":init");
	}

	@Override
	protected void doFilter(HttpServletRequest req, HttpServletResponse res, FilterChain chain)
			throws IOException, ServletException {
		print(":doFilter");
		String paramBean;
		paramBean = req.getParameter("CBean");
		if (paramBean == null) {
			res.getWriter().write("Error: Wrong CBean value. Value can not be NULL!");
			return;
		}
		chain.doFilter(req, res);
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
