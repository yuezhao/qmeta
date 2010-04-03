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
QMeta relies on the Qitty library, which is a toolkit to enhance the Qt library. You can find this project at http://github.com/ollix/qitty.

Because QMeta is a library for Qt, you also need the Qt library installed in
order to use it. Further, Qitty uses CMake to build itself, so you may need to
know how it works.

Getting the Source
------------------
Currently QMeta is at early state and do not have any release yet. The only
way you can get the source code is to clone the source from this QMeta's Git
repository. Git is a popular Distributed Version Control System (DVCS), if you
have no idea about what it is, please refer to the Git's website:
http://git-scm.com/

Building the Source
-------------------
Here's the common process to build Qitty using CMake with GNU Makefile:

1. mkdir build
2. cd build
3. cmake ..
4. make
5. make install

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
