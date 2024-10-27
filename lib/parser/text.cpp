#include <cmath>
#include <cstdint>
#include <ctime>

#include "text.hpp"

uint32_t toInt(const char *text) {
  int num = 0;
  for (int i = 0; i < static_cast<int>(strLen(text)); i++) {
    num +=
        (pow(10, static_cast<int>(strLen(text) - i - 1))) * (text[i] - '0');
  }
  return num;
}
void strCopy(char *dest, const char *src, int n) {
  for (int i = 0; i < n; ++i) {
    dest[i] = src[i];
  }
  if (dest[n - 1] != '\0') {
    dest[n] = '\0';
  }
}
std::size_t strLen(const char *s) {
  std::size_t length = 0;
  while (s[++length] != '\0') {
  }
  return length;
}

void strCat(char *dest, const char *src, int n) {
  std::size_t length = strLen(dest);
  for (int i = 0; i < n; ++i) {
    dest[length + i] = src[i];
  }
  if (dest[length + n - 1] != '\0') {
    dest[length + n] = '\0';
  }
}

int strCmp(const char *left, const char *right) {
  int index = 0;
  while (left[index] != '\0' && right[index] != '\0') {
    if (left[index] != right[index]) {
      return 1;
    }
    ++index;
  }
  if (left[index] == right[index]) {
    return 0;
  }
  return 1;
}

int strnCmp(const char *left, const char *right, int n) {
  for (int i = 0; i < n; ++i) {
    if (left[i] != right[i]) {
      return 1;
    }
    if ((left[i] == '\0' || right[i] == '\0') && i != n - 1) {
      return 1;
    }
  }
  return 0;
}
