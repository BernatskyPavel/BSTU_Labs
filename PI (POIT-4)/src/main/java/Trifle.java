

import java.applet.Applet;
import java.awt.Color;
import java.awt.Graphics;

@Deprecated
public class Trifle extends Applet {

	/**
	 * 
	 */
	private static final long serialVersionUID = 6561277045998567805L;

	private String lighthouse;

	@Override
	public void init() {
		setBackground(Color.CYAN);
		setForeground(Color.RED);
		lighthouse = "--init--";
	}

	@Override
	public void start() {
		lighthouse += "--start--";
	}

	@Override
	public void paint(Graphics g) {
		lighthouse += "--paint--";
		g.drawString(this.lighthouse, 10, 30);
	}

	@Override
	public void stop() {
		lighthouse += "--stop--";
	}

	@Override
	public void destroy() {
		lighthouse += "--destroy--";
		super.destroy();
	}

}
