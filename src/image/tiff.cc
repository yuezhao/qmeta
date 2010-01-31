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
#include <qitty/byte_array.h>

namespace qmeta_image {

Tiff::Tiff(QWidget *parent) : QObject(parent) {}

// Opens a TIFF file with the specified file_path. Returns true if the specified
// file_path is a valid TIFF file and initialization is completed.
bool Tiff::Open(const QString &file_path) {
  QFile file(file_path, this);
  file.open(QIODevice::ReadOnly);
  // Reads the first two bytes from the image file header to determine the
  // endianness of the Tiff file.
  QByteArray endianness_bytes = file.read(2);
  if (endianness_bytes == "II")
    set_endianness(kLittleEndians);
  else if (endianness_bytes == "MM")
    set_endianness(kBigEndians);
  else
    return false;

  // Further identifies the file whether is a TIFF file by reading the next two
  // bytes in the image file header. The value of these two bytes should equal
  // to 42 in decimal, which means the two bytes is represented as "002a" in
  // hexidecimal in big-endian byte order.
  QByteArray fourty_two_bytes = file.read(2);
  // Coverts the bytes to big-endian byte order if the TIFF file uses the
  // little-endian byte order.
  if (endianness() == kLittleEndians)
    fourty_two_bytes = qitty_utils::ReverseByteArray(fourty_two_bytes);
  if (fourty_two_bytes.toHex() != "002a")
    return false;
  return true;
}

}  // namespace qmeta_image
