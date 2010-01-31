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

#include "file_types/tiff.h"

#include <QtGui>
#include <qitty/byte_array.h>

namespace qmeta {

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
  // bytes in the image file header. The value should equal to 42 in decimal.
  QByteArray fourty_two_bytes = file.read(2);
  // Coverts the bytes to big-endian byte order if the TIFF file uses the
  // little-endian byte order.
  if (endianness() == kLittleEndians)
    fourty_two_bytes = qitty_utils::ReverseByteArray(fourty_two_bytes);
  if (!qitty_utils::EqualToInt(fourty_two_bytes, 42))
    return false;

  // Reads the offset of the first IFD by reading the next 4 bytes in the
  // image file header.
  QByteArray first_ifd_offset_bytes = file.read(4);
  // Coverts the bytes to big-endian byte order if the TIFF file uses the
  // little-endian byte order.
    if (endianness() == kLittleEndians) {
    first_ifd_offset_bytes =
        qitty_utils::ReverseByteArray(first_ifd_offset_bytes);
  }
  int first_ifd_offset = qitty_utils::ToInt(first_ifd_offset_bytes);
  if (first_ifd_offset > 7)
    set_first_ifd_offset(first_ifd_offset);
  else
    return false;

  return true;
}

}  // namespace qmeta
