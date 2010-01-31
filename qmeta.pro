# Copyright 2010, Ollix
# All rights reserved.
#
# This file is part of QMeta.
#
# QMeta is free software: you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free
# Software Foundation, either version 3 of the License, or any later version.
#
# QMeta is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
# for more details.
#
# You should have received a copy of the GNU General Public License
# along with QMeta. If not, see <http://www.gnu.org/licenses/>.

# ---
# Author: olliwang@ollix.com (Olli Wang)
#
# QMeta - a library to manipulate file_types metadata based on Qt.
#
# This is the project file that required by qmake to build the QMeta library.
# You may need to modify this file to adapt your environment.

TEMPLATE = lib
TARGET = qmeta
VERSION = 0.1
CONFIG += release qt
QT = core
DESTDIR = dist

# Sets directories for build files.
MOC_DIR = build/moc
OBJECTS_DIR = build/objects
RCC_DIR = build/resources
UI_DIR = build/ui

# Source code files for the QMeta.
INCLUDEPATH = src
HEADERS += src/exif.h \
           src/file_type.h \
           src/tiff.h \
           src/jpeg.h
SOURCES += src/exif.cc \
           src/file_type.cc \
           src/tiff.cc \
           src/jpeg.cc

unix {
    headers.files = $$HEADERS
    headers.path = /usr/include/$${TARGET}
    target.path = /usr/lib
    INSTALLS += headers target

    # Qitty
    INCLUDEPATH *= /usr/include
    LIBS += -lqitty
}
