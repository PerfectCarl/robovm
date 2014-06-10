package libcore.io;

public class Windows extends ForwardingOs implements Os, WinOs {

	public Windows() {
		super(new Posix());
	}
	
	public native boolean pathIsRelative(String path);

}
