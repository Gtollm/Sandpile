#pragma once

#include <cstddef>
#include <cstdint>
#include <filesystem>

#include "lib/matrix/matrix.hpp"
#include "lib/vector/vector.hpp"

class BmpWriter {
 private:
  utils::Vector<int> colorPalette = {0xFFFFFF,  // White
                                     0x00FF00,  // Green
                                     0x800080,  // Purple
                                     0xFFFF00,  // Yellow
                                     0x000000};

#pragma pack(push, 1)
  struct BMPHeader {
    uint16_t bfType{0x4D42};
    uint32_t bfSize{0};
    uint16_t bfReserved1{0};
    uint16_t bfReserved2{0};
    uint32_t bfOffBits{54};
    void SetSize(std::size_t size);
  };

  struct DIBHeader {
    uint32_t biSize{40};
    int32_t biWidth{0};
    int32_t biHeight{0};
    uint16_t biPlanes{1};
    uint16_t biBitCount{4};
    uint32_t biCompression{0};
    uint32_t biSizeImage{0};
    int32_t biXPelsPerMeter{2835};
    int32_t biYPelsPerMeter{2835};
    uint32_t biClrUsed{5};
    uint32_t biClrImportant{5};
    void SetDimensions(std::size_t width, std::size_t height);
  };
#pragma pack(pop)

  inline uint8_t GetColor(std::size_t ind);

 public:
  BmpWriter()
      : colorPalette({
            0xFFFFFF,  // White
            0x00FF00,  // Green
            0x800080,  // Purple
            0xFFFF00,  // Yellow
            0x000000   // Black
        }) {}
  void WriteBmp(const char* filename,
                const utils::Matrix<uint64_t>& pixelData);
  char* GetPath(const char* path_dir, const char* file_name, int);
  void CreateDir(const char* dir_name);
};
