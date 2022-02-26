package lab09.filters;

import java.io.IOException;

import jakarta.servlet.FilterChain;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpFilter;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

public class F2 extends HttpFilter {

	/**
	 * 
	 */
	private static final long serialVersionUID = 3450206032818378648L;

	@Override
	public void init() throws ServletException {
		super.init();
		print(":init");
	}

	@Override
	protected void doFilter(HttpServletRequest req, HttpServletResponse res, FilterChain chain)
			throws IOException, ServletException {
		print(":doFilter");
		String referer = req.getHeader("Referer");
		if (referer != null && referer.contains("/Lab09")) {
			chain.doFilter(req, res);
			return;
		} else {
			res.sendRedirect("./blocked.xhtml");
		}
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
