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
// This file implements the detail of the Exif class.

#include "exif.h"

#include <QtCore>

#include <qitty/byte_array.h>

namespace qmeta {

Exif::Exif(QObject *parent) : QObject(parent) {}

// Initializes the Exif object by storing the specified file and
// tiff_header_offset. It also determines the byte order and the offset of
// the first IFD. Returns true if the TIFF header is valid.
bool Exif::Init(QFile *file, const int tiff_header_offset) {
  set_tiff_header_offset(tiff_header_offset);
  set_file(file);

  file->seek(tiff_header_offset);
  // Determines the byte order in the specified file.
  QByteArray byte_order = file->read(2);
  if (byte_order == "II")
    set_endianness(kLittleEndians);
  else if (byte_order == "MM")
    set_endianness(kBigEndians);
  else
    return false;

  // Further identifies whether the specified file has a valid TIFF header.
  // Reads the next two bytes which should have the value of 42 in decimal.
  QByteArray fourty_two = ReadFromFile(2);
  if (!qitty_utils::EqualToInt(fourty_two, 42))
    return false;

  // Reads the next four bytes to determine the offset of the first IFD.
  int first_ifd_offset = qitty_utils::ToInt(ReadFromFile(4));
  // Sets the offset to the current position if the read value equals to 8.
  // The reason is for JPEG files, if the TIFF header is followed immediately
  // by the first IFD, it is written as 00000008 in hexidecimal.
  if (first_ifd_offset == 8)
    first_ifd_offset = file->pos();
  else if (first_ifd_offset != -1)
    return false;
  set_first_ifd_offset(first_ifd_offset);

  return true;
}

// Reads at most max_size bytes from the tracked file object, and returns the
// data read as a QByteArray in big-endian byte order.
QByteArray Exif::ReadFromFile(const int max_size) {
  QByteArray data = file()->read(max_size);
  if (endianness() == kLittleEndians)
    data = qitty_utils::ReverseByteArray(data);
  return data;
}

}  // namespace qmeta
