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

Jpeg::Jpeg(QByteArray *data) : File(data) {
  InitMetadata();
}

Jpeg::Jpeg(QIODevice *file) : File(file) {
  InitMetadata();
}

Jpeg::Jpeg(const QString &file_name) : File(file_name) {
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
  file()->seek(2);
  while (!file()->atEnd()) {
    // Find APP1 marker.
    if (file()->read(1).toHex() != "ff")
      continue;
    if (file()->read(1).toHex() != "e1")
      continue;

    // Retrieves the APP1 length. The length doesn't include the APP1 marker.
    file()->read(2).toHex().toInt(NULL, 16);

    // Checks the Exif Identifier Code.
    if (file()->read(6).toHex() == "457869660000")
      break;
  }

  if (file()->atEnd())
    return;

  // Creates the Exif object.
  Exif *exif = new Exif(this);
  if (exif->Init(file(), file()->pos(), kJpegFileType))
    set_exif(exif);
}

// Reimplements the File::InitIptc().
void Jpeg::InitIptc() {
  // Finds the APP13 marker.
  file()->seek(2);
  while (!file()->atEnd()) {
    if (file()->read(1).toHex() != "ff")
      continue;
    if (file()->read(1).toHex() != "ed")
      continue;
    break;
  }
  // Returns if there is not APP13 marker.
  if (file()->atEnd())
    return;

  // Skips the ";xPhotoshop 3.0" string.
  QByteArray c = file()->read(16);

  bool found_iptc = false;
  // Interators the Image Resource Blocks to find IPTC data. If found, sets the
  // `found_iptc` to true and gets out of the loop.
  while (QString(file()->read(4)) == "8BIM") {
    int identifier = file()->read(2).toHex().toInt(NULL, 16);
    // Skips the variable name in Pascal string, padded to make the size even.
    // A null name consists of two bytes of 0.
    int name_length = file()->read(1).toHex().toInt(NULL, 16);
    if (name_length == 0)
      file()->read(1);
    else if (name_length % 2 == 1)
      file()->read(name_length);
    else
      file()->read(name_length + 1);
    // Determines the actual size of resource data that follows.
    int data_length = file()->read(4).toHex().toInt(NULL, 16);
    // Determines if the current block is used to record the IPTC data.
    // If true, the identifier should be 1028 in decimal.
    if (identifier == 1028) {
      found_iptc = true;
      break;
    } else {
      file()->read(data_length);
    }
  }
  // Returns if there is no IPTC data.
  if (!found_iptc)
    return;

  int iptc_pos = file()->pos();
  // TODO (olliwang): creates the IPTC object according to the found position.
}

}  // namespace qmeta
