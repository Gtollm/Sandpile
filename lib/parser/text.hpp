#pragma once

#include <cstdint>
#include <ctime>

uint32_t toInt(const char *text);
void strCopy(char *dest, const char *src, int n);
std::size_t strLen(const char *s);
void strCat(char *dest, const char *src, int n);
int strCmp(const char *left, const char *right);
int strnCmp(const char *left, const char *right, int n);
