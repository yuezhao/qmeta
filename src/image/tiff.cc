// Copyright 2010, Ollix
// All rights reserved.
//
// This file is part of QMeta.
//
// QMeta is free software: you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free
// Software Foundation, either version 3 of the License, or any later version.
//
// QMeta is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
// for more details.
//
// You should have received a copy of the GNU General Public License
// along with QMeta. If not, see <http://www.gnu.org/licenses/>.

// ---
// Author: olliwang@ollix.com (Olli Wang)
//
// QMeta - a library to manipulate image metadata based on Qt.
//
// This file implements the detail of the TIFF class.

#include "image/tiff.h"

#include <QtGui>

namespace qmeta_image {

TIFF::TIFF(QWidget *parent) : QObject(parent) {}

// Initializes a TIFF file with the specified file_path. Returns true if the
// specified file_path is a valid TIFF file and initialization is completed.
bool TIFF::Init(const QString &file_path) {
  QFile file(file_path);
  file.open(QIODevice::ReadOnly);
  // Determines the endianness.
  QString endianness = file.read(2);
  if (endianness == "II")
    set_endianness(kLittleEndians);
  else if (endianness == "MM")
    set_endianness(kBigEndians);
  else
    return false;
  return true;
}

}  // namespace qmeta_image
