package org.robovm.compiler.toolchain;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

import org.apache.commons.io.FileUtils;
import org.robovm.compiler.config.Arch;
import org.robovm.compiler.config.Config;
import org.robovm.compiler.config.OS;
import org.robovm.compiler.util.ToolchainUtil;

public class DarwinToolchain extends Toolchain {

    public DarwinToolchain(Config config, Arch arch, OS os) {
        super(config, arch, os);
    }

    @Override
    public void writeObjectFiles(File objectsFile, List<File> objectFiles)
            throws IOException {

        // The Xcode linker doesn't need paths with spaces to be quoted and
        // will fail if we do quote
        FileUtils.writeLines(objectsFile, objectFiles, "\n");

    }

    @Override
    public List<String> getOptions(File objectsFile) {
        List<String> opts = new ArrayList<String>();
        if (config.isDebug()) {
            opts.add("-g");
        }
        opts.add("-arch");
        opts.add(arch.getClangName());
        opts.add("-Wl,-filelist," + objectsFile.getAbsolutePath());

        return opts;
    }

    private static String IOS_DEV_CLANG;
    private static String IOS_SIM_CLANG;

    public static String getIOSDevClang() throws IOException {
        if (IOS_DEV_CLANG == null) {
            IOS_DEV_CLANG = ToolchainUtil.findXcodeCommand("clang++", "iphoneos");
        }
        return IOS_DEV_CLANG;
    }

    public static String getIOSSimClang() throws IOException {
        if (IOS_SIM_CLANG == null) {
            IOS_SIM_CLANG = ToolchainUtil.findXcodeCommand("clang++", "iphonesimulator");
        }
        return IOS_SIM_CLANG;
    }

    @Override
    public String getGccpPath() {
        String ccPath = "clang++";
        File binPath = config.getCcBinPath();
        if (binPath != null) {
            ccPath = binPath.getAbsolutePath();
        } else if (os == OS.ios) {
            try {
                if (arch == Arch.x86) {
                    ccPath = getIOSSimClang();
                } else {
                    ccPath = getIOSDevClang();
                }
            } catch (IOException e) {
                // TODO : CARL : process error
            }
        }
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
        libs.add("-force_load");
        libs.add(new File(config.getOsArchDepLibDir(), "librobovm-rt"
                + libSuffix + ".a").getAbsolutePath());
        if (config.isSkipInstall()) {
            libs.add("-lrobovm-debug" + libSuffix);
        }

        libs.addAll(Arrays.asList("-lrobovm-core" + libSuffix, "-lgc"
                + libSuffix, "-lpthread", "-ldl", "-lm"));

        libs.add("-liconv");
        libs.add("-lsqlite3");
        libs.add("-framework");
        libs.add("Foundation");

        ccArgs.add("-L");
        ccArgs.add(config.getOsArchDepLibDir().getAbsolutePath());

        File exportedSymbolsFile = new File(config.getTmpDir(),
                "exported_symbols");
        List<String> exportedSymbols = new ArrayList<String>();
        if (config.isSkipInstall()) {
            exportedSymbols.add("catch_exception_raise");
        }
        exportedSymbols.addAll(config.getExportedSymbols());
        for (int i = 0; i < exportedSymbols.size(); i++) {
            // On Darwin symbols are always prefixed with a '_'. We'll
            // prepend
            // '_' to each symbol here so the user won't have to.
            exportedSymbols.set(i, "_" + exportedSymbols.get(i));
        }
        FileUtils.writeLines(exportedSymbolsFile, "ASCII", exportedSymbols);
        ccArgs.add("-exported_symbols_list");
        ccArgs.add(exportedSymbolsFile.getAbsolutePath());
        ccArgs.add("-Wl,-no_implicit_dylibs");
        ccArgs.add("-Wl,-dead_strip");

        if (config.getOs() == OS.macosx) {
            ccArgs.add("-mmacosx-version-min=10.6");
        }

        if (!config.getFrameworks().isEmpty()) {
            for (String p : config.getFrameworks()) {
                libs.add("-framework");
                libs.add(p);
            }
        }
        if (!config.getWeakFrameworks().isEmpty()) {
            for (String p : config.getWeakFrameworks()) {
                libs.add("-weak_framework");
                libs.add(p);
            }
        }

        if (!config.getLibs().isEmpty()) {
            objectFiles = new ArrayList<File>(objectFiles);
            for (Config.Lib lib : config.getLibs()) {
                String p = lib.getValue();
                if (p.endsWith(".o")) {
                    objectFiles.add(new File(p));
                } else if (p.endsWith(".a")) {
                    // .a file

                    if (lib.isForce()) {
                        libs.add("-force_load");
                    }
                    libs.add(new File(p).getAbsolutePath());
                } else {
                    // link via -l if suffix is omitted
                    libs.add("-l" + p);
                }
            }
        }

        this.link(ccArgs, objectFiles, libs, outFile);
    }
}
