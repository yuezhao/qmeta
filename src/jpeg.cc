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
// QMeta - a library to manipulate file_types metadata based on Qt.
//
// This file implements the detail of the Jpeg class.

#include "jpeg.h"

#include <QtCore>
#include <qitty/byte_array.h>

#include "exif.h"

namespace qmeta {

Jpeg::Jpeg(QObject *parent) : File(parent) {}

Jpeg::Jpeg(QByteArray *data, QObject *parent) : File(data, parent) {
  InitMetadata();
}

Jpeg::Jpeg(QIODevice *file, QObject *parent) : File(file, parent) {
  InitMetadata();
}

Jpeg::Jpeg(const QString &file_name, QObject *parent) : File(file_name,
                                                             parent) {
  InitMetadata();
}

// Reimplements the File::IsValid().
bool Jpeg::IsValid() {
  if (!file())
    return false;

  // Checks the first 2 bytes if equals to the SOI marker.
  file()->seek(0);
  if (file()->read(2).toHex() != "ffd8")
    return false;

  return true;
}

// Reimplements the File::InitExif().
void Jpeg::InitExif() {
  if (!IsValid())
    return;

  // Jumps to the beginning of the APP1 marker.
  file()->seek(2);
  // Checks the APP1 marker.
  if (file()->read(2).toHex() != "ffe1")
    return;

  // Retrieves the APP1 length. The length doesn't include the APP1 marker.
  file()->read(2).toHex().toInt(NULL, 16);

  // Checks the Exif Identifier Code.
  if (file()->read(6).toHex() != "457869660000")
    return;

  // Creates the Exif object.
  Exif *exif = new Exif(this);
  if (exif->Init(file(), file()->pos(), kJpegFileType))
    set_exif(exif);
}

}  // namespace qmeta
