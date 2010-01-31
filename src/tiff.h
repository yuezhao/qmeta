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
// This file defines the TIFF class.

#ifndef QMETA_TIFF_H_
#define QMETA_TIFF_H_

#include "file_type.h"

class QString;

namespace qmeta {

class Tiff : public FileType {
 public:
  explicit Tiff(QObject *parent = NULL);
  bool Open(const QString &file_path);

 protected:
  virtual bool CreateExifObject();

 private:
  enum Endianness {
    kLittleEndians = 0,
    kBigEndians
  };
  enum FieldTypes {
    BYTE = 1,
    ASCII = 2,
    SHORT = 3,
    LONG = 4,
    RATIONAL = 5,
    SBYTE = 6,
    UNDEFINED = 7,
    SSHORT = 8,
    SLONG = 9,
    SRATIONAL = 10,
    FLOAT = 11,
    DOUBLE = 12
  };

  Endianness endianness() const { return endianness_; }
  void set_endianness(Endianness endianness) { endianness_ = endianness; }
  int first_ifd_offset() const { return first_ifd_offset_; }
  void set_first_ifd_offset(int offset) { first_ifd_offset_ = offset; }

  // The byte order of the TIFF file.
  Endianness endianness_;
  // The offset (in bytes) of the first IFD.
  int first_ifd_offset_;
};

}  // namespace qmeta

#endif  // QMETA_TIFF_H_
