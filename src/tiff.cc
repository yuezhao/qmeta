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

#include "tiff.h"

#include <QtCore>
#include <qitty/byte_array.h>

#include "exif.h"
#include "tiff_header.h"

namespace qmeta {

Tiff::Tiff(QByteArray *data) : File(data) {
  Init();
}

Tiff::Tiff(QIODevice *file) : File(file) {
  Init();
}

Tiff::Tiff(const QString &file_name) : File(file_name) {
  Init();
}

// Initializes the Tiff object.
void Tiff::Init() {
  if (!file())
    return;

  TiffHeader *tiff_header = new TiffHeader(this);
  if (tiff_header->Init(file(), 0))
    set_tiff_header(tiff_header);
  else
    set_tiff_header(NULL);

  InitMetadata();
}

// Reimplements the File::IsValid().
bool Tiff::IsValid() {
  if (!file())
    return false;

  if (tiff_header())
    return true;
  else
    return false;
}

// Reimplements the File::InitExif().
void Tiff::InitExif() {
  if (tiff_header()) {
    // Creates the Exif object.
    Exif *exif = new Exif(this);
    if (exif->Init(file(), tiff_header()))
      set_exif(exif);
    else
      delete exif;
  }
}

}

}  // namespace qmeta
