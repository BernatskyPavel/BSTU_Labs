package lab05.tags;

import java.io.IOException;

import jakarta.servlet.jsp.JspException;
import jakarta.servlet.jsp.tagext.SimpleTagSupport;

public class Submit extends SimpleTagSupport {

	@Override
	public void doTag() throws JspException, IOException {
		getJspContext().getOut().write(
				"<input type='submit' name='bpv-submit' value='Submit'/><input type='reset' name='bpv-reset' value='Reset'/><br/>");
	}
}
