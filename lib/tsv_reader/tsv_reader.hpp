#pragma once

#include <concepts>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "lib/sandpile/sandpile.hpp"

class TsvReader {
 private:
  const std::size_t kMLineLength = 64;

  template <std::integral T>
  T FindElement(char*& ptr) {
    char* end = ptr;
    while (*end != '\t' && *end != '\0') {
      end++;
    }

    std::size_t length = end - ptr;
    std::string field(ptr, length);
    ptr = (*end == '\t') ? end + 1 : end;
    T res;
    if constexpr (std::is_same_v<T, uint64_t>) {
      res = std::stoull(field);
    } else {
      res = static_cast<T>(std::atoi(field.c_str()));
    }
    return res;
  }

 public:
  void ParseTSV(const char* filename, Sandpile* pile) {
    std::ifstream file(filename);
    if (!file.is_open()) {
      std::cerr << "Error opening file: " << filename << std::endl;
      return;
    }

    char* line = new char[kMLineLength];
    while (file.getline(line, kMLineLength)) {
      char* ptr = line;
      uint16_t x = FindElement<uint16_t>(ptr);
      uint16_t y = FindElement<uint16_t>(ptr);
      uint64_t val = FindElement<uint64_t>(ptr);
      pile->SetPoint(x, y, val);
      if (val > 4) {
        pile->AddToUnsteady(x, y);
      }
    }
    delete[] line;
  }
};
