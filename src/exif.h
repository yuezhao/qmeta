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

#ifndef QMETA_EXIF_H_
#define QMETA_EXIF_H_

#include <QObject>

#include "identifiers.h"

class QFile;
template<class T, class U> class QHash;

namespace qmeta {

class Exif : public QObject {
  Q_OBJECT

 public:
  // TIFF Rev. 6.0 attribute information used in Exif, represented in decimal.
  enum TagNames {
    // Tags relating to image data structure.
    kImageWidth = 256,  // Image width
    kImageLength = 257,  // Image height
    kBitsPerSample  = 258,  // Number of bits per component
    kCompression = 259,  // Compression scheme
    kPhotometricInterpretation = 262,  // Pixel composition
    kOrientation = 274,  // Orientation of image
    kSamplesPerPixel = 277,  // Number of components
    kPlanarConfiguration = 284,  // Image data arrangement
    kYCbCrSubSampling = 530,  // Subsampling ratio of Y to C
    kYCbCrPositioning = 531,  // Y and C positioning
    kXResolution = 282,  // Image resolution in width direction
    kYResolution = 283,  // Image resolution in height direction
    kResolutionUnit = 296,  // Unit of X and Y resolution
    // Tags relating to recording offset.
    kStripOffsets = 273,  // Image data location
    kRowsPerStrip = 278,  // Number of rows per strip
    kStripByteCounts = 279,  // Bytes per compressed strip
    kJPEGInterchangeFormat = 513,  // Offset to JPEG SOI
    kJPEGInterchangeFormatLength = 514,  // Bytes of JPEG data
    // Tags relating to image data characteristics.
    kTransferFunction = 301,  // Transfer function
    kWhitePoint = 318,  // White point chromaticity
    kPrimaryChromaticities = 319,  // Chromaticities of primaries
    kYCbCrCoefficients = 529,  // Color space transformation matrix coefficients
    kReferenceBlackWhite = 532,  // Pair of black and white reference values
    // Other tags.
    kDateTime = 306,  // File change date and time
    kImageDescription = 270,  // Image title
    kMake = 271,  // Image input equipment manufacturer
    kModel = 272,  // Image input equipment model
    kSoftware = 305,  // Software used
    kArtist = 315,  // Person who created the image
    kCopyright = 33432,  // Copyright holder
  };

  explicit Exif(QObject *parent = NULL);
  bool Init(QFile *file, const int tiff_header_offset, FileTypes type);
  bool ReadIfdEntry(int ifd_entry_offset);
  bool ReadIfds();
  bool ReadIfds(int ifd_offset);

 private:
  // Field types are used in Exif.
  enum FieldTypes {
    // An 8-bit unsigned integer.
    kByteFiledType = 1,
    // An 8-bit byte containing one 7-bit ASCII code. The final byte is
    // terminated with NULL.
    kAsciiFiedType = 2,
    // A 16-bit (2-byte) unsigned integer.
    kShortFiledType = 3,
    // A 32-bit (4-byte) unsigned integer.
    kLongFieldType = 4,
    // Two LONGs. The first LONG is the numerator and the second LONG expresses
    // the denominator.
    kRationalFieldType = 5,
    // An 8-bit byte that can take any value depending ont he field definition.
    kUndefinedFieldType = 7,
    // A 32-bit (4-byte) signed integer (2's complement notation)
    kSlongFieldType = 9,
    // Two SLONGs. The first SLONG is the numerator and the second SLONG is the
    // denominator.
    kSrationalFieldType = 10,
  };

  QByteArray ReadFromFile(const int max_size);
  QByteArray ReadIfdEntryValue(const int offset, const int bytes);

  Endianness endianness() const { return endianness_; }
  void set_endianness(Endianness endian) { endianness_ = endian; }
  QHash<TagNames, QString>* tag_names() const { return tag_names_; }
  void set_tag_names(QHash<TagNames, QString> *tag_names) {
    tag_names_ = tag_names;
  }
  QFile* file() const { return file_; }
  void set_file(QFile *file) { file_ = file; }
  int first_ifd_offset() const { return first_ifd_offset_; }
  void set_first_ifd_offset(int offset) { first_ifd_offset_ = offset; }
  FileTypes file_type() const { return file_type_; }
  void set_file_type(FileTypes type) { file_type_ = type; }
  int tiff_header_offset() const { return tiff_header_offset_; }
  void set_tiff_header_offset(int offset) { tiff_header_offset_ = offset; }

  // The byte order of the TIFF file.
  Endianness endianness_;
  // The tag names to read for human.
  QHash<TagNames, QString> *tag_names_;
  // Tracks the file containing this EXIF data.
  QFile *file_;
  // The offset of the first IFD.
  int first_ifd_offset_;
  // The type of the tracked file.
  FileTypes file_type_;
  // The offset of the TIFF header.
  int tiff_header_offset_;
};

}  // namespace qmeta

#endif  // QMETA_EXIF_H_
