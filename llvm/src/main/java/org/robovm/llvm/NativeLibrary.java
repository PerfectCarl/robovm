/*
 * Copyright (C) 2013 Trillian AB
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/gpl-2.0.html>.
 */
package org.robovm.llvm;

import java.io.BufferedOutputStream;
import java.io.Closeable;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import javax.management.RuntimeErrorException;

import org.robovm.llvm.binding.LLVM;

/**
 * 
 */
public class NativeLibrary {
    private static boolean loaded = false;
    private static final String os;
    private static final String arch;
    private static final String libName;

    static {
        String osProp = System.getProperty("os.name").toLowerCase();
        String archProp = System.getProperty("os.arch").toLowerCase();
        if (osProp.startsWith("mac") || osProp.startsWith("darwin")) {
            os = "macosx";
            libName = "librobovm-llvm" + ".dylib";
        } else if (osProp.startsWith("linux")) {
            os = "linux";
            libName = "librobovm-llvm" + ".so";
        } else if (osProp.startsWith("windows")) {
            os = "windows";
            libName = "librobovm-llvm" + ".dll";
        } else {
            throw new Error("Unsupported OS: " + System.getProperty("os.name"));
        }
        if ("windows".equals(os)) {
            String model = System.getProperty("sun.arch.data.model");
            if ("32".equals(model))
                arch = "x86";
            else if ("64".equals(model))
                arch = "x86_64";
            else
                throw new Error("Unsupported sun.arch.data.model: " + model);

        } else {
            if (archProp.matches("amd64|x86[-_]64")) {
                arch = "x86_64";
            } else if (archProp.matches("i386|x86")) {
                arch = "x86";
            } else {
                throw new Error("Unsupported arch: "
                        + System.getProperty("os.arch"));
            }
        }
    }

    public static synchronized void load() {
        if (loaded) {
            return;
        }

        String prefix = libName.substring(0, libName.lastIndexOf('.'));
        String ext = libName.substring(libName.lastIndexOf('.'));

        String path = "binding/" + os + "/" + arch + "/" + libName;
        System.out.println("Loading: " + path);
        InputStream in = NativeLibrary.class.getResourceAsStream(path);
        if (in == null) {
            throw new UnsatisfiedLinkError("Native library for " + os + "-"
                    + arch + " not found. Path: " + path);
        }
        OutputStream out = null;
        File tmpLibFile = null;
        try {
            tmpLibFile = File.createTempFile(prefix, ext);
            tmpLibFile.deleteOnExit();
            out = new BufferedOutputStream(new FileOutputStream(tmpLibFile));
            copy(in, out);
        } catch (IOException e) {
            throw (Error) new UnsatisfiedLinkError(e.getMessage()).initCause(e);
        } finally {
            closeQuietly(in);
            closeQuietly(out);
        }

        path= tmpLibFile.getAbsolutePath() ;

        boolean result=true;
        try {
            Runtime.getRuntime().load(path);
            result = !LLVM.StartMultithreaded();
        } catch (Throwable e) {
            String message = "Error while loading: " +path ;
            throw new RuntimeException(message, e) ;
        }
        if (result) {
            String message = "LLVMStartMultithreaded failed while loading: " +path ;
            throw new UnsatisfiedLinkError(message);
        }

        LLVM.InitializeAllTargets();
        LLVM.InitializeAllTargetInfos();
        LLVM.InitializeAllTargetMCs();
        LLVM.InitializeAllAsmPrinters();
        LLVM.InitializeAllAsmParsers();
    }

    private static void copy(InputStream in, OutputStream out)
            throws IOException {
        byte[] buffer = new byte[4096];
        int n = 0;
        while ((n = in.read(buffer)) != -1) {
            out.write(buffer, 0, n);
        }
    }

    private static void closeQuietly(Closeable in) {
        try {
            if (in != null) {
                in.close();
            }
        } catch (IOException ioe) {
        }
    }
}
