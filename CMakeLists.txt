# Copyright 2010, Ollix
# All rights reserved.
#
# This file is part of Qitty.
#
# Qitty is free software: you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free
# Software Foundation, either version 3 of the License, or any later version.
#
# Qitty is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
# for more details.
#
# You should have received a copy of the GNU General Public License
# along with Qitty. If not, see <http://www.gnu.org/licenses/>.

# ---
# Author: olliwang@ollix.com (Olli Wang)
#
# QMeta - a library to manipulate image metadata based on Qt.

cmake_minimum_required(VERSION 2.8.1)

project(QMETA)

find_package("Qt4" REQUIRED)
set(QT_DONT_USE_QTGUI True)
include(${QT_USE_FILE})

find_library(QITTY_LIBRARY NAMES Qitty PATHS "qitty.h")

include_directories("${PROJECT_SOURCE_DIR}/include" ${QT_INCLUDE_DIR})

file(GLOB QMETA_SRCS "src/*.cc")
file(GLOB QMETA_HEADERS "include/qmeta/*.h")

QT4_WRAP_CPP(QMETA_MOC_SRCS ${QMETA_HEADERS})

add_library(qmeta SHARED ${QMETA_SRCS} ${QMETA_MOC_SRCS})
target_link_libraries(qmeta ${QT_LIBRARIES} ${QITTY_LIBRARY})
install(TARGETS qmeta DESTINATION lib)
install(DIRECTORY "include/qmeta" DESTINATION "include"
        FILES_MATCHING PATTERN "*.h")
