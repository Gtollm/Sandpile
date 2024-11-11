#include "lib/sandpile/sandpile.hpp"
#include "tsv_reader.hpp"

template <std::integral T>
T TsvReader::FindElement(char*& ptr) {
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

void TsvReader::ParseTSV(const char* filename, Sandpile* pile) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error opening file: " << filename << std::endl;
    return;
  }

  char* line = new char[kMLineLength];
  bool first = true;
  while (file.getline(line, kMLineLength)) {
    char* ptr = line;
    uint16_t x = FindElement<uint16_t>(ptr);
    uint16_t y = FindElement<uint16_t>(ptr);
    uint64_t val = FindElement<uint64_t>(ptr);
    if (first) {
      pile->GetMatrix().SetXNormalization(-x);
      pile->GetMatrix().SetYNormalization(-y);
      first = false;
    }
    pile->SetPoint(x, y, val);
    if (val > 4) {
      pile->AddToUnsteady(x, y);
    }
  }
  delete[] line;
}
