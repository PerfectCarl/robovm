package org.robovm.compiler.toolchain;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import org.robovm.compiler.config.Arch;
import org.robovm.compiler.config.Config;
import org.robovm.compiler.config.OS;
import org.robovm.compiler.util.Executor;

public abstract class Toolchain {

    private static Toolchain NativeWindow = null;
    private static Toolchain Linux = null;
    private static Toolchain Darwin = null;

    Arch arch;
    OS os;
    Config config;

    public Toolchain(Config config, Arch arch, OS os) {
        super();
        this.config = config;
        this.arch = arch;
        this.os = os;
    }

    public static Toolchain getToolchain(Config config, Arch arch, OS os) {
        // FIXME: write this for other platforms
        if (NativeWindow == null)
            NativeWindow = new NativeWindowsToolchain(config, arch, os);
        return NativeWindow;
    }

    abstract public void writeObjectFiles(File objectsFile,
            List<File> objectFiles) throws IOException;

    abstract public List<String> getOptions(File objectsFile);

    abstract public String getGccpPath();

    abstract public void linkAbstract(List<File> objectFiles)
            throws IOException;

    public void link(List<String> args, List<File> objectFiles,
            List<String> libs, File outFile) throws IOException {
        Toolchain toolchain = Toolchain.getToolchain(config, config.getArch(),
                config.getOs());
        if (toolchain == null) {
            // CARL TODO report error
            return;
        }
        File objectsFile = new File(config.getTmpDir(), "objects");
        toolchain.writeObjectFiles(objectsFile, objectFiles);
        List<String> opts = toolchain.getOptions(objectsFile);
        if (opts != null)
            opts.addAll(args);
        else
            opts = new ArrayList<String>();

        new Executor(config.getLogger(), toolchain.getGccpPath()).args("-o",
                outFile, opts, libs).exec();
    }
}
