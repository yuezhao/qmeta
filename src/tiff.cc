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

#include "tiff.h"

#include <QtCore>
#include <qitty/byte_array.h>

#include "exif.h"

namespace qmeta {

Tiff::Tiff(QObject *parent) : File(parent) {}

Tiff::Tiff(QByteArray *data, QObject *parent) : File(data, parent) {
  InitMetadata();
}

Tiff::Tiff(QIODevice *file, QObject *parent) : File(file, parent) {
  InitMetadata();
}

Tiff::Tiff(const QString &file_name, QObject *parent) : File(file_name,
                                                             parent) {
  InitMetadata();
}

// Reimplements the File::IsValid().
bool Tiff::IsValid() {
  if (!file())
    return false;

  file()->seek(0);
  // Determines the byte order in the specified file.
  QByteArray byte_order = file()->read(2);
  QByteArray fourty_two = file()->read(2);
  if (byte_order == "II")
    // The byte order is little-endian. Exchanges the bytes in fourty_two.
    fourty_two = qitty_utils::ReverseByteArray(fourty_two);
  else if (byte_order == "MM")
    // The byte order is big-endian. No need to change the bytes in fourty_two.
    fourty_two = fourty_two;
  else
    return false;

  // Further identifies whether the specified file has a valid TIFF header.
  // The fourty_two should have the value of 42 in decimal.
  if (fourty_two.toHex().toInt(NULL, 16) != 42)
    return false;

  return true;
}

// Reimplements the File::InitExif().
void Tiff::InitExif() {
  if (IsValid()) {
    // Creates the Exif object.
    Exif *exif = new Exif(this);
    if (exif->Init(file(), 0, kTiffFileType))
      set_exif(exif);
  }
}

}  // namespace qmeta
