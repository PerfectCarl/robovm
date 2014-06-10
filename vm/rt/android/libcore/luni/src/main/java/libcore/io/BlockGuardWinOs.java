package libcore.io;

public class BlockGuardWinOs extends BlockGuardOs implements WinOs {
    public BlockGuardWinOs(WinOs os) {
        super(os);
    }

    public boolean pathIsRelative(String path) {
        return ((WinOs)this.os).pathIsRelative(path);
    }
}
