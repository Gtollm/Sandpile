#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "bmp.hpp"

const char* kSlash = "/";
const char* kExt = ".bmp";

void BmpWriter::BMPHeader::SetSize(std::size_t size) { this->bfSize = size; }
void BmpWriter::DIBHeader::SetDimensions(std::size_t width,
                                         std::size_t height) {
  this->biWidth = width;
  this->biHeight = height;
  this->biSizeImage = ((width + 1) / 2) * height;
}

inline uint8_t BmpWriter::GetColor(std::size_t ind) {
  if (ind >= colorPalette.size() - 1) {
    return colorPalette.size() - 1;
  }
  return ind % colorPalette.size();
}

void BmpWriter::WriteBmp(const char* filename,
                         const utils::Matrix<uint64_t>& pixelData) {
  std::ofstream file(filename, std::ios::binary);

  if (!file) {
    std::cerr << "Could not open file for writing: " << filename
              << std::endl;
    return;
  }

  BMPHeader bmpHeader;
  DIBHeader dibHeader;
  dibHeader.biWidth = pixelData.GetWidth();
  dibHeader.biHeight = pixelData.GetHeight();
  dibHeader.SetDimensions(pixelData.GetWidth(), pixelData.GetHeight());
  bmpHeader.SetSize(sizeof(BMPHeader) + sizeof(DIBHeader) +
                    dibHeader.biSizeImage + colorPalette.size() * 4);

  file.write(reinterpret_cast<char*>(&bmpHeader), sizeof(bmpHeader));
  file.write(reinterpret_cast<char*>(&dibHeader), sizeof(dibHeader));

  for (const int& color : colorPalette) {
    uint8_t blue = color & 0xFF;
    uint8_t green = (color >> 8) & 0xFF;
    uint8_t red = (color >> 16) & 0xFF;
    uint8_t reserved = 0;
    file.write(reinterpret_cast<char*>(&blue), 1);
    file.write(reinterpret_cast<char*>(&green), 1);
    file.write(reinterpret_cast<char*>(&red), 1);
    file.write(reinterpret_cast<char*>(&reserved), 1);
  }

  int rowSize = ((dibHeader.biWidth + 1) / 2 + 3) & ~3;
  utils::Vector<uint8_t> rowData(static_cast<std::size_t>(rowSize), 0);

  // Write pixel data with each row padded to align to 4 bytes
  for (int y = dibHeader.biHeight - 1; y >= 0; --y) {
    for (int x = 0; x < dibHeader.biWidth; x += 2) {
      uint8_t byte =
          (GetColor(pixelData.at(y, x)) << 4) |
          (x + 1 < dibHeader.biWidth
               ? static_cast<uint8_t>(GetColor(pixelData.at(y, x + 1)))
               : 0);
      rowData[x / 2] = byte;
    }
    file.write(reinterpret_cast<char*>(rowData.data()), rowSize);
  }

  file.close();
}

char* BmpWriter::GetPath(const char* file_name, int number) {
  std::size_t path_len = strlen(this->dir_name);
  std::size_t file_len = strlen(file_name);
  std::size_t total_len = path_len + file_len + 52 + 2;
  char* full_path = new char[total_len];

  strcpy(full_path, this->dir_name);

  if (path_len > 0 && this->dir_name[path_len - 1] != '/') {
    strcat(full_path, "/");
  }
  char new_file_name[256];
  if (number != -1) {
    snprintf(new_file_name, sizeof(new_file_name), "%s_%d.bmp", file_name,
             number);
  } else {
    snprintf(new_file_name, sizeof(new_file_name), "%s_complete.bmp",
             file_name);
  }
  strcat(full_path, new_file_name);
  return full_path;
}

void BmpWriter::SetDir(const char* dir_name) { this->dir_name = dir_name; }

void BmpWriter::CreateDir() {
  if (!std::filesystem::exists(this->dir_name)) {
    try {
      std::filesystem::create_directory(this->dir_name);
    } catch (const std::filesystem::filesystem_error& e) {
      std::cerr << "Error creating directory: " << e.what() << std::endl;
      return;
    }
  }
}
