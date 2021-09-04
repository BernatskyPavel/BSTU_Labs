package lab13.helpers;

import java.io.File;
import java.io.FilenameFilter;

public class DocFilter {
	private String[] filelist;

	private class Filter implements FilenameFilter {
		String type;

		public Filter(String type) {
			this.type = type;
		}

		@Override
		public boolean accept(File dir, String name) {
			return name.endsWith(this.type);
		}
	}

	public DocFilter(String file, String type) {
		File dir = new File(file);
		if (dir.exists()) {
			this.filelist = dir.list(new DocFilter.Filter(type));
		}
	}

	public String[] getFilelist() {
		return filelist;
	}
}
