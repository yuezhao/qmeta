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
// This file defines the File class which is the base class for all QMeta
// supported file types.

#ifndef QMETA_FILE_H_
#define QMETA_FILE_H_

#include <QObject>

class QIODevice;

namespace qmeta {

class Exif;

class File : public QObject {
 public:
  explicit File(QObject *parent = NULL);
  explicit File(QByteArray *data, QObject *parent = NULL);
  explicit File(QIODevice *file, QObject *parent = NULL);
  explicit File(const QString &file_name, QObject *parent = NULL);
  Exif* exif() const { return exif_; }
  QByteArray Thumbnail();

 protected:
  void set_exif(Exif *exif) { exif_ = exif; }
  QIODevice* file() const { return file_; }
  // Initializes the Exif object.
  virtual void InitExif() {};
  void InitMetadata();

 private:
  // Returns true if the tracked file is valid. This function should be
  // reimplemented in all subclasses to verify specific file types.
  virtual bool IsValid() { return false; }

  void set_file(QIODevice *file) { file_ = file; }

  // The corresponded Exif object of the tracked file. This property is set
  // if the tracked file supports the EXIF specification.
  Exif *exif_;
  // Tracks the current opened file.
  QIODevice *file_;
};

}  // namespace qmeta

#endif  // QMETA_FILE_H_
