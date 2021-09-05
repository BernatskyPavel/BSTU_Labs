package lab05.tags;

import java.io.IOException;

import jakarta.servlet.jsp.JspException;
import jakarta.servlet.jsp.tagext.SimpleTagSupport;

public class Surname extends SimpleTagSupport {

	@Override
	public void doTag() throws JspException, IOException {
		getJspContext().getOut().write("Surname: <input type='text' name='bpv-surname'/><br/>");
	}

}
