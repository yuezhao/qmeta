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
// This file defines the Exif class.

#ifndef QMETA_EXIF_H_
#define QMETA_EXIF_H_

#include <QObject>

#include "identifiers.h"

class QFile;

namespace qmeta {

class Exif : public QObject {
 public:
  explicit Exif(QObject *parent = NULL);
  bool Init(QFile *file, const int tiff_header_offset);

 private:
  QByteArray ReadFromFile(const int max_size);

  Endianness endianness() const { return endianness_; }
  void set_endianness(Endianness endian) { endianness_ = endian; }
  QFile* file() const { return file_; }
  void set_file(QFile *file) { file_ = file; }
  int first_ifd_offset() const { return first_ifd_offset_; }
  void set_first_ifd_offset(int offset) { first_ifd_offset_ = offset; }
  int tiff_header_offset() const { return tiff_header_offset_; }
  void set_tiff_header_offset(int offset) { tiff_header_offset_ = offset; }

  // The byte order of the TIFF file.
  Endianness endianness_;
  // Tracks the file containing this EXIF data.
  QFile *file_;
  // The offset of the first IFD.
  int first_ifd_offset_;
  // The offset of the TIFF header.
  int tiff_header_offset_;
};

}  // namespace qmeta

#endif  // QMETA_EXIF_H_
