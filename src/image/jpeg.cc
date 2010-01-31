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
// This file defines the Jpeg class.

#include "image/jpeg.h"

#include <QtGui>

namespace qmeta_image {

Jpeg::Jpeg(QWidget *parent) : QObject(parent) {}

// Opens a JPEG file with the specified file_path. Returns true if the specified
// file_path is a valid JPEG file and initialization is completed.
bool Jpeg::Open(const QString &file_path) {
  return true;
}

}  // namespace qmeta_image
