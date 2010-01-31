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

#ifndef QMETA_METADATA_TYPES_EXIF_H_
#define QMETA_METADATA_TYPES_EXIF_H_

#include <QObject>

namespace qmeta {

class Exif : public QObject {
 public:
  explicit Exif(QObject *parent = NULL);
};

}  // namespace qmeta

#endif  // QMETA_METADATA_TYPES_EXIF_H_
