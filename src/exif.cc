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
// This file implements the detail of the Exif class.

#include "exif.h"

#include <QtCore>

#include <qitty/byte_array.h>

namespace qmeta {

Exif::Exif(QObject *parent) : QObject(parent) {
  InitTagNames();
}

// Initializes the Exif object by storing the specified file and
// tiff_header_offset. It also determines the byte order and the offset of
// the first IFD. Returns true if the TIFF header is valid.
bool Exif::Init(QFile *file, const int tiff_header_offset, FileTypes type) {
  set_tiff_header_offset(tiff_header_offset);
  set_file(file);
  set_file_type(type);

  file->seek(tiff_header_offset);
  // Determines the byte order in the specified file.
  QByteArray byte_order = file->read(2);
  if (byte_order == "II")
    set_endianness(kLittleEndians);
  else if (byte_order == "MM")
    set_endianness(kBigEndians);
  else
    return false;

  // Further identifies whether the specified file has a valid TIFF header.
  // Reads the next two bytes which should have the value of 42 in decimal.
  if (ReadFromFile(2).toHex().toInt(NULL, 16) != 42)
    return false;

  // Reads the next four bytes to determine the offset of the first IFD.
  int first_ifd_offset = ReadFromFile(4).toHex().toInt(NULL, 16);
  // Sets the offset to the current position if the read value equals to 8.
  // The reason is for JPEG files, if the TIFF header is followed immediately
  // by the first IFD, it is written as 00000008 in hexidecimal.
  if (first_ifd_offset == 8)
    first_ifd_offset = file->pos();
  else if (first_ifd_offset == -1)
    return false;
  set_first_ifd_offset(first_ifd_offset);

  return true;
}

// Initializes tag names used in Exif.
void Exif::InitTagNames() {
  QHash<TagNames, QString> *tag_names = new QHash<TagNames, QString>;
  // Exif-specific IFD.
  tag_names->insert(kExifIfdPointer, tr("Exif IFD Pointer"));
  tag_names->insert(kGpsInfoIfdPointer, tr("GPS Info IFD Pointer"));
  tag_names->insert(kInteroperabilityIfdPointer,
                    tr("Interoperability IFD Pointer"));
  // TIFF Rev. 6.0 attribute information used in Exif.
  tag_names->insert(kImageWidth, tr("Image Width"));
  tag_names->insert(kImageLength, tr("Image Height"));
  tag_names->insert(kBitsPerSample, tr("Bits Per Sample"));
  tag_names->insert(kCompression, tr("Compression"));
  tag_names->insert(kPhotometricInterpretation,
                      tr("Photometric Interpretation"));
  tag_names->insert(kOrientation, tr("Orientation"));
  tag_names->insert(kSamplesPerPixel, tr("Samples Per Pixel"));
  tag_names->insert(kPlanarConfiguration, tr("Planar Configuration"));
  tag_names->insert(kYCbCrSubSampling, tr("YCbCr Sub Sampling"));
  tag_names->insert(kYCbCrPositioning, tr("YCbCr Positioning"));
  tag_names->insert(kXResolution, tr("X-Resolution"));
  tag_names->insert(kYResolution, tr("Y-Resolution"));
  tag_names->insert(kResolutionUnit, tr("Resolution Unit"));
  tag_names->insert(kStripOffsets, tr("Strip Offsets"));
  tag_names->insert(kRowsPerStrip, tr("Rows Per Strip"));
  tag_names->insert(kStripByteCounts, tr("Strip Byte Counts"));
  tag_names->insert(kJPEGInterchangeFormat, tr("JPEG Interchange Format"));
  tag_names->insert(kJPEGInterchangeFormatLength,
                      tr("JPEG Interchange Format Length"));
  tag_names->insert(kTransferFunction, tr("Transfer Function"));
  tag_names->insert(kWhitePoint, tr("White Point"));
  tag_names->insert(kPrimaryChromaticities, tr("Primary Chromaticities"));
  tag_names->insert(kYCbCrCoefficients, tr("YCbCr Coefficients"));
  tag_names->insert(kReferenceBlackWhite, tr("Reference Black White"));
  tag_names->insert(kDateTime, tr("Date Time"));
  tag_names->insert(kImageDescription, tr("Image Description"));
  tag_names->insert(kMake, tr("Make"));
  tag_names->insert(kModel, tr("Model"));
  tag_names->insert(kSoftware, tr("Software"));
  tag_names->insert(kArtist, tr("Artist"));
  tag_names->insert(kCopyright, tr("Copyright"));
  // The attribute information recorded in the Exif IFD.
  tag_names->insert(kExifVersion, tr("Exif Version"));
  tag_names->insert(kFlashpixVersion, tr("Flashpix Version"));
  tag_names->insert(kColorSpace, tr("Color Space"));
  tag_names->insert(kComponentsConfiguration, tr("Components Configuration"));
  tag_names->insert(kCompressedBitsPerPixel, tr("Compressed Bits Per Pixel"));
  tag_names->insert(kPixelXDimension, tr("Pixel X Dimension"));
  tag_names->insert(kPixelYDimension, tr("Pixel Y Dimension"));
  tag_names->insert(kMakerNote, tr("Maker Note"));
  tag_names->insert(kUserComment, tr("User Comment"));
  tag_names->insert(kRelatedSoundFile, tr("Related Sound File"));
  tag_names->insert(kDateTimeOriginal, tr("Date Time Original"));
  tag_names->insert(kDateTimeDigitized, tr("Date Time Digitized"));
  tag_names->insert(kSubSecTime, tr("Sub Sec Time"));
  tag_names->insert(kSubSecTimeOriginal, tr("Sub Sec Time Original"));
  tag_names->insert(kSubSecTimeDigitized, tr("Sub Sec Time Digitized"));
  tag_names->insert(kExposureTime, tr("Exposure Time"));
  tag_names->insert(kFNumber, tr("F Number"));
  tag_names->insert(kExposureProgram, tr("Exposure Program"));
  tag_names->insert(kSpectralSensitivity, tr("Spectral Sensitivity"));
  tag_names->insert(kISOSpeedRatings, tr("ISO Speed Rating"));
  tag_names->insert(kOECF, tr("Optoelectric conversion factor"));
  tag_names->insert(kShutterSpeedValue, tr("Shutter Speed"));
  tag_names->insert(kApertureValue, tr("Aperture Value"));
  tag_names->insert(kBrightnessValue, tr("Brightness"));
  tag_names->insert(kExposureBiasValue, tr("Exposure Bias"));
  tag_names->insert(kMaxApertureValue, tr("Maximum Lens Aperture"));
  tag_names->insert(kSubjectDistance, tr("Subject Distance"));
  tag_names->insert(kMeteringMode, tr("Metering Mode"));
  tag_names->insert(kLightSource, tr("Light Source"));
  tag_names->insert(kFlash, tr("Flash"));
  tag_names->insert(kFocalLength, tr("Focal Length"));
  tag_names->insert(kSubjectArea, tr("Subject Area"));
  tag_names->insert(kFlashEnergy, tr("Flash Energy"));
  tag_names->insert(kSpatialFrequencyResponse,
                    tr("Spatial Frequency Response"));
  tag_names->insert(kFocalPlaneXResolution, tr("Focal Plane X Resolution"));
  tag_names->insert(kFocalPlaneYResolution, tr("Focal Plane Y Resolution"));
  tag_names->insert(kFocalPlaneResolutionUnit,
                    tr("Focal Plane Resolution Unit"));
  tag_names->insert(kSubjectLocation, tr("Subject Location"));
  tag_names->insert(kExposureIndex, tr("Exposure Index"));
  tag_names->insert(kSensingMethod, tr("Sensing Method"));
  tag_names->insert(kFileSource, tr("File Source"));
  tag_names->insert(kSceneType, tr("Scene Type"));
  tag_names->insert(kCFAPattern, tr("CFA Pattern"));
  tag_names->insert(kCustomRendered, tr("Custom Rendered"));
  tag_names->insert(kExposureMode, tr("Exposure Mode"));
  tag_names->insert(kWhiteBalance, tr("White Balance"));
  tag_names->insert(kDigitalZoomRatio, tr("Digital Zoom Ratio"));
  tag_names->insert(kFocalLengthIn35mmFilm, tr("Focal Length In 35mm Film"));
  tag_names->insert(kSceneCaptureType, tr("Scene Capture Type"));
  tag_names->insert(kGainControl, tr("Gain Control"));
  tag_names->insert(kContrast, tr("Contrast"));
  tag_names->insert(kSaturation, tr("Saturation"));
  tag_names->insert(kSharpness, tr("Sharpness"));
  tag_names->insert(kDeviceSettingDescription,
                    tr("Device Setting Description"));
  tag_names->insert(kSubjectDistanceRange, tr("Subject Distance Range"));
  tag_names->insert(kImageUniqueID, tr("Image Unique ID"));
  set_tag_names(tag_names);
}

// Reads a 12-byte IFD entry at the specified ifd_entry_offset. Returns false
// only if the format is not correct.
bool Exif::ReadIfdEntry(int ifd_entry_offset) {
  file()->seek(ifd_entry_offset);
  // Reads the tag that identifies the field.
  QByteArray tag = ReadFromFile(2);
  TagNames tag_name = static_cast<TagNames>(tag.toHex().toInt(NULL, 16));
  if (tag_names()->contains(tag_name))
    qDebug() << "Tag:" << tag_names()->value(tag_name);
  else
    return true;

  // Reads the field type.
  int type = ReadFromFile(2).toHex().toInt(NULL, 16);
  // Reads the number of values of the indicated Type.
  int count = ReadFromFile(4).toHex().toInt(NULL, 16);

  // Retrieves the value of the IFD entry.
  int bytes;  // The number of bytes used for the entry value.
  QByteArray value;  // The entry value.
  switch (static_cast<FieldTypes>(type)) {
    case kByteFiledType:
      qDebug() << "Type: BYTE";
      bytes = 1 * count;
      value = ReadIfdEntryValue(file()->pos(), bytes);
      qDebug() << value.toHex().toUShort(NULL, 16);
      break;
    case kAsciiFiedType:
      qDebug() << "Type: ASCII";
      bytes = 1 * count;
      value = ReadIfdEntryValue(file()->pos(), bytes);
      qDebug() << QString(value);
      break;
    case kShortFiledType:
      qDebug() << "Type: SHORT";
      bytes = 2 * count;
      value = ReadIfdEntryValue(file()->pos(), bytes);
      qDebug() << value.toHex().toUShort(NULL, 16);
      break;
    case kLongFieldType:
      qDebug() << "Type: LONG";
      bytes = 4 * count;
      value = ReadIfdEntryValue(file()->pos(), bytes);
      qDebug() << value.toHex().toULong(NULL, 16);
      break;
    case kRationalFieldType:
      qDebug() << "Type: RATIONAL";
      bytes = 8 * count;
      value = ReadIfdEntryValue(file()->pos(), bytes);
      qDebug() << value.toHex();
      break;
    case kUndefinedFieldType:
      qDebug() << "Type: UNDEFINED";
      bytes = 1 * count;
      value = ReadIfdEntryValue(file()->pos(), bytes);
      qDebug() << value.toHex();
      qDebug() << QString(value);
      break;
    case kSlongFieldType:
      qDebug() << "Type: SLONG";
      bytes = 4 * count;
      value = ReadIfdEntryValue(file()->pos(), bytes);
      qDebug() << value.toHex().toLong(NULL, 16);
      break;
    case kSrationalFieldType:
      qDebug() << "Type: SRATIONAL";
      bytes = 8 * count;
      value = ReadIfdEntryValue(file()->pos(), bytes);
      qDebug() << value.toHex();
      break;
    default:
      return false;
  }

  if (tag_name == kExifIfdPointer) {
    qDebug() << "^^^^^^^^^^^^ Exif ^^^^^^^^^^^^^^";
    ReadIfds(value.toHex().toULong(NULL, 16));
    qDebug() << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^";
  }

  qDebug() << "--------------------------------";
  return true;
}

// Returns the value of the IFD entry from the specified value_offset.
QByteArray Exif::ReadIfdEntryValue(const int value_offset, const int bytes) {
  file()->seek(value_offset);
  // Jumps to the offset if the specified bytes is greater than 4.
  if (bytes > 4) {
    int offset = ReadFromFile(4).toHex().toInt(NULL, 16) + tiff_header_offset();
    file()->seek(offset);
  }
  return file()->read(bytes);
}

// Reads IFDs recursively from the first IFD. Returns true if successful.
bool Exif::ReadIfds() {
  return ReadIfds(first_ifd_offset());
}

// Reads IFDs recursively from the specified ifd_offset. Returns true if
// successful.
bool Exif::ReadIfds(int ifd_offset) {
  file()->seek(ifd_offset);
  // Reads the 2-byte count of the number of directory entries.
  int entry_count = ReadFromFile(2).toHex().toInt(NULL, 16);
  qDebug() << "Entry count: " << entry_count;
  qDebug() << "--------------------------------";

  // Reads a sequence of 12-byte field entries.
  for (int i = 0; i < entry_count; ++i) {
    int ifd_entry_offset = (ifd_offset + 2) + (i * 12);
    if (!ReadIfdEntry(ifd_entry_offset)) {
      qDebug() << "IFD Entry Error";
      return false;
    }
  }

  // Reads the offset of the next IFD.
  file()->seek((ifd_offset + 2) + (entry_count * 12));
  int next_ifd_offset = ReadFromFile(4).toHex().toInt(NULL, 16);
  if (next_ifd_offset == -1) {
    return false;
  } else if (next_ifd_offset == 0) {
    return true;
  } else {
    if (file_type() == kJpegFileType)
      next_ifd_offset = next_ifd_offset + first_ifd_offset() - 8;
    qDebug() << "Next IFD offset: " << next_ifd_offset;
    qDebug() << "################################";
    return ReadIfds(next_ifd_offset);
  }
}

// Reads at most max_size bytes from the tracked file object, and returns the
// data read as a QByteArray in big-endian byte order.
QByteArray Exif::ReadFromFile(const int max_size) {
  QByteArray data = file()->read(max_size);
  if (endianness() == kLittleEndians)
    data = qitty_utils::ReverseByteArray(data);
  return data;
}

}  // namespace qmeta