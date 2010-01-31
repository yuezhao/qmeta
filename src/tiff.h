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
  enum FieldTypes {
    kByteFiledType = 1,
    kAsciiFiedType = 2,
    kShortFiledType = 3,
    kLongFieldType = 4,
    kRationalFieldType = 5,
    kSbyteFieldType = 6,
    kUndefinedFieldType = 7,
    kSshortFieldType = 8,
    kSlongFieldType = 9,
    kSrationalFieldType = 10,
    kFloatFieldType = 11,
    kDoubleFieldType = 12,
  };

  explicit Tiff(QObject *parent = NULL);
  bool Open(const QString &file_path);
};

}  // namespace qmeta

#endif  // QMETA_TIFF_H_
