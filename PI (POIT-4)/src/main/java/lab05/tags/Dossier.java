package lab05.tags;

import java.io.IOException;

import jakarta.servlet.jsp.JspException;
import jakarta.servlet.jsp.tagext.BodyTagSupport;

public class Dossier extends BodyTagSupport {

	/**
	 * 
	 */
	private static final long serialVersionUID = -1343858651943276756L;

	private String action;

	public final String getAction() {
		return action;
	}

	public final void setAction(String action) {
		this.action = action;
	}

	@Override
	public int doStartTag() throws JspException {
		try {
			pageContext.getOut().write("<form name='bpv-form' method='POST' action='" + getAction() + "'>");
		} catch (IOException e) {
			System.out.println("Dossier:StartTag: " + e.getMessage());
		}
		return EVAL_BODY_INCLUDE;
	}

	@Override
	public int doEndTag() throws JspException {
		try {
			pageContext.getOut().write("</form>");
		} catch (IOException e) {
			System.out.println("Dossier:EndTag: " + e.getMessage());
		}
		return EVAL_BODY_INCLUDE;
	}

}
