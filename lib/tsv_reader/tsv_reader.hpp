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
  T FindElement(char*& ptr);

 public:
  void ParseTSV(const char* filename, Sandpile* pile);
};
