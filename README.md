Action lines
=========

A custom GEGL operation (and by extension GIMP filter) that makes action lines
![image](https://github.com/LinuxBeaver/GEGL-Action-Lines/assets/78667207/90d098a7-d509-43a4-8491-44e699826338)

## OS specific location to put GEGL Filter binaries 

Windows
 C:\\Users\<YOUR NAME>\AppData\Local\gegl-0.4\plug-ins
 
 Linux 
`~/.local/share/gegl-0.4/plug-ins`
 
 Linux (Flatpak)
`~/.var/app/org.gimp.GIMP/data/gegl-0.4/plug-ins`


## Compiling and Installing
Simply run build_plugin_linux/windows.sh - to understand what it does manually read this

### Linux

To compile and install you will need the GEGL header files (`libgegl-dev` on
Debian based distributions or `gegl` on Arch Linux) and meson (`meson` on
most distributions).

```bash
meson setup --buildtype=release build
ninja -C build
```

If you have an older version of gegl you may need to copy to `~/.local/share/gegl-0.3/plug-ins`
instead (on Ubuntu 18.04 for example).

### Windows

The easiest way to compile this project on Windows is by using msys2.  Download
and install it from here: https://www.msys2.org/

Open a msys2 terminal with `C:\msys64\mingw64.exe`.  Run the following to
install required build dependencies:

```bash
pacman --noconfirm -S base-devel mingw-w64-x86_64-toolchain mingw-w64-x86_64-meson mingw-w64-x86_64-gegl
```

Then build the same way you would on Linux:

```bash
meson setup --buildtype=release build
ninja -C build
```

## Previews of this based plugin

![image](https://raw.githubusercontent.com/LinuxBeaver/GEGL-GIMP-PLUGIN_Action_Lines/main/preview_action_lines.png)


