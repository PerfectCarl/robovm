package org.robovm.compiler.toolchain;

import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

import org.apache.commons.io.IOUtils;
import org.robovm.compiler.config.Arch;
import org.robovm.compiler.config.Config;
import org.robovm.compiler.config.OS;

public class LinuxToolchain extends Toolchain {

    public LinuxToolchain(Config config, Arch arch, OS os) {
        super(config, arch, os);
    }

    @Override
    public void writeObjectFiles(File objectsFile, List<File> objectFiles)
            throws IOException {

        // The linker on Linux will fail if we don't quote paths with spaces
        BufferedOutputStream objectsOut = null;
        try {
            objectsOut = new BufferedOutputStream(new FileOutputStream(
                    objectsFile));
            for (File f : objectFiles) {
                objectsOut.write('"');
                objectsOut.write(f.getAbsolutePath().getBytes());
                objectsOut.write('"');
                objectsOut.write('\n');
            }
        } finally {
            IOUtils.closeQuietly(objectsOut);
        }

    }

    @Override
    public List<String> getOptions(File objectsFile) {
        List<String> opts = new ArrayList<String>();
        if (config.isDebug()) {
            opts.add("-g");
        }

        opts.add("-m32");
        opts.add("@" + objectsFile.getAbsolutePath());

        return opts;
    }

    @Override
    public String getGccpPath() {
        String ccPath = "g++";
        File binPath = config.getCcBinPath();
        if (binPath != null)
            ccPath = binPath.getAbsolutePath();

        return ccPath;
    }

    @Override
    public void linkAbstract(List<File> objectFiles) throws IOException {
        // TODO : CARL : toolchainutil
        File outFile = new File(config.getTmpDir(), config.getExecutableName());

        config.getLogger().debug("Building executable %s", outFile);

        LinkedList<String> ccArgs = new LinkedList<String>();
        LinkedList<String> libs = new LinkedList<String>();

        String libSuffix = config.isUseDebugLibs() ? "-dbg" : "";

        libs.add("-lrobovm-bc" + libSuffix);

        libs.addAll(Arrays.asList("-Wl,--whole-archive", "-lrobovm-rt"
                + libSuffix, "-Wl,--no-whole-archive"));

        if (config.isSkipInstall()) {
            libs.add("-lrobovm-debug" + libSuffix);
        }

        libs.addAll(Arrays.asList("-lrobovm-core" + libSuffix, "-lgc"
                + libSuffix, "-lpthread", "-ldl", "-lm"));

        libs.add("-lrt");

        ccArgs.add("-L");
        ccArgs.add(config.getOsArchDepLibDir().getAbsolutePath());

        ccArgs.add("-Wl,-rpath=$ORIGIN");
        ccArgs.add("-Wl,--gc-sections");
        // ccArgs.add("-Wl,--print-gc-sections");

        if (!config.getLibs().isEmpty()) {
            objectFiles = new ArrayList<File>(objectFiles);
            for (Config.Lib lib : config.getLibs()) {
                String p = lib.getValue();
                if (p.endsWith(".o")) {
                    objectFiles.add(new File(p));
                } else if (p.endsWith(".a")) {
                    // .a file

                    if (lib.isForce()) {
                        libs.add("-Wl,--whole-archive");
                    }
                    libs.add(new File(p).getAbsolutePath());
                    if (lib.isForce()) {
                        libs.add("-Wl,--no-whole-archive");
                    }
                } else {
                    // link via -l if suffix is omitted
                    libs.add("-l" + p);
                }
            }
        }

        this.link(ccArgs, objectFiles, libs, outFile);
    }
}
