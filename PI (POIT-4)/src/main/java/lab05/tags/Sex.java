package lab05.tags;

import java.io.IOException;

import jakarta.servlet.jsp.JspException;
import jakarta.servlet.jsp.tagext.SimpleTagSupport;

public class Sex extends SimpleTagSupport {

	@Override
	public void doTag() throws JspException, IOException {
		getJspContext().getOut().write(
				"Sex: <input type='radio' name='bpv-sex' value='Male' checked/>Male<input type='radio' name='bpv-sex' value='Female'/>Female<br/>");
	}
}
