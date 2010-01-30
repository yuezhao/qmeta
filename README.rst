QMeta
=====
http://github.com/ollix/qmeta


Overview
--------
QMeta is a library to manipulate image metadata based on Qt. The goal is to
support EXIF, XMP and IPTC on all popular image formats from JPEG, TIFF to
various raw image files seamlessly with Qt applications.

Requirements
------------
Because QMeta is a library for Qt, you need the Qt library installed in order
to use it. Further, QMeta uses qmake (part of Qt) to build itself, so you may
need to know how it works.

Getting the Source
------------------
Currently QMeta is at early state and do not have any release yet. The only
way you can get the source code is to clone the source from this QMeta's Git
repository. Git is a popular Distributed Version Control System (DVCS), if you
have no idea about what it is, please refer to the Git's website:
http://git-scm.com/

Building the Source
-------------------
QMeta uses qmake to generate the Makefile on unix-like platforms. It could
also build on Windows, but not tested and implemented in the project file
(qmeta.pro). Here's the simply steps to build the source under unix-like
platforms. First, you need to switch to the top directory of the source (the
directory containing `qmeta.pro` file). Then uses qmake to generate a
Makefile.

    qmake qmeta.pro

Once you have the Makefile, you can build it as usually.

    make

The generated library files will be put in the `dist` directory. By default,
they are dynamic libraries, and you can install them to your operating system.

    make install

This command will install QMeta's header files in the `/usr/include/qmeta`
directory, and dynamic library files in the `/usr/lib/` directory by default.

Contribution
------------
The source code commonly follows the `Google's C++ Style Guide
<http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml>`_, with fews
exceptions that limited by Qt.

License
-------
QMeta is available under GPLv3 or later license.

Copyright (c) 2010 Ollix. All rights reserved.

QMeta is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation, either version 3 of the License, or any later version.

QMeta is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with QMeta. If not, see <http://www.gnu.org/licenses/>.
