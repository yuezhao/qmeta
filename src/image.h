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
// This file defines the Image class, which has the ability to guess the file
// type of the specified image data, and can be used as a normal file class
// such as Jpeg, Tiff, etc.

#ifndef QMETA_IMAGE_H_
#define QMETA_IMAGE_H_

#include "exif.h"
#include "file.h"
#include "identifiers.h"
#include "jpeg.h"
#include "tiff.h"

namespace qmeta {

class Image : public File {
public:
  explicit Image(QObject *parent = NULL);
  explicit Image(QByteArray *data, QObject *parent = NULL);
  explicit Image(QIODevice *file, QObject *parent = NULL);
  explicit Image(const QString &file_name, QObject *parent = NULL);
  bool IsValid();

  FileType file_type() const { return file_type_; }

 private:
  void GuessType();
  template<class T> bool GuessType(FileType file_type);

  void set_file_type(FileType file_type) { file_type_ = file_type; }
  FileType file_type_;
};

}  // namespace qmeta

#endif  // QMETA_IMAGE_H_
