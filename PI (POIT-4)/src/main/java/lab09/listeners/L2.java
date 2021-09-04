package lab09.listeners;

import jakarta.servlet.http.HttpSessionAttributeListener;
import jakarta.servlet.http.HttpSessionBindingEvent;

public class L2 implements HttpSessionAttributeListener {

	@Override
	public void attributeAdded(HttpSessionBindingEvent event) {
		HttpSessionAttributeListener.super.attributeAdded(event);
		print(":Attribute Added");
	}

	@Override
	public void attributeRemoved(HttpSessionBindingEvent event) {
		HttpSessionAttributeListener.super.attributeRemoved(event);
		print(":Attribute Removed");
	}

	@Override
	public void attributeReplaced(HttpSessionBindingEvent event) {
		HttpSessionAttributeListener.super.attributeReplaced(event);
		print(":Attribute Replaced");
	}

	private void print(String msg) {
		System.out.println(this.getClass().getName() + msg);
	}
}
