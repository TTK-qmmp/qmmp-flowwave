This is a plugin for Qmmp (1.4.0 or greater) visual.

![Image](https://github.com/TTK-qmmp/qmmp-flowwave/blob/master/image/1.png?raw=true)

The following packages are required, including development headers,
which some vendors split into separate packages:

- qmmp
- qt5

To build, run Qt5's qmake (often installed as qmake-qt5) and then build
with make:

$ qmake-qt5
$ make

To install:

$ make install

This installs the plugin into Qmmp's visual plugin directory.  To install
to a staging area, such as for packaging:

$ make install INSTALL_ROOT=/path/to/staging