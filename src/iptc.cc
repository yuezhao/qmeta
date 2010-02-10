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
// This file implements the detail of the Iptc class.

#include "iptc.h"

#include <QtCore>

namespace qmeta {

Iptc::Iptc(QObject *parent) : Standard(parent) {}

bool Iptc::Init(QIODevice *file, const int offset) {
  file->seek(offset);
  while (file->read(2).toHex() == "1c02") {
    qDebug() << "--------------";
    int tag = file->read(1).toHex().toInt(NULL, 16);
    qDebug() << "Tag:" << tag;
    int size = file->read(2).toHex().toInt(NULL, 16);
    QByteArray data = file->read(size);
    qDebug() << "Data:" << data;
  }
  return true;
}

}  // namespace qmeta
