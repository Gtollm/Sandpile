#pragma once

#include <cstdint>
#include <initializer_list>
#include <utility>

#include "lib/vector/vector.hpp"

namespace utils {

enum class Direction { RIGHT, LEFT, DOWN, UP, ALL };

template <typename T>
class Matrix {
 public:
  Matrix();
  Matrix(std::size_t height, std::size_t width);
  Matrix(const std::initializer_list<std::initializer_list<T>>& data);
  Matrix(const Vector<Vector<T>>& data);
  Matrix<T>& operator=(const Matrix<T>& obj);
  Matrix<T>& operator=(
      const std::initializer_list<std::initializer_list<T>>& data);
  virtual ~Matrix();
  void clear();
  void Extend(Direction dr, std::size_t size = 1);
  Vector<T>& operator[](std::size_t row);
  const Vector<T>& operator[](std::size_t row) const;
  Vector<T> GetRow(std::size_t row) const;
  Vector<T> GetCollumn(std::size_t collumn) const;
  T GetElement(std::size_t row, std::size_t collumn) const;
  std::size_t GetWidth() const;
  std::size_t GetHeight() const;
  std::pair<std::size_t, std::size_t> GetNormalization() const;
  std::int16_t GetXNormalized(std::int16_t x) const;
  std::int16_t GetYNormalized(std::int16_t y) const;
  T& at(std::size_t row, std::size_t collumn);
  const T& at(std::size_t row, std::size_t collumn) const;
  void set(std::size_t row, std::size_t collumn, const T& val);
  void SetElement(std::size_t row, std::size_t collumn, const T& val);
  void SetUElement(std::int16_t urow, std::int16_t ucollumn, const T& val);
  void SetRow(std::size_t row, const T& val);
  void SetNormalization(std::size_t x, std::size_t y);
  void SetXNormalization(std::size_t x);
  void SetYNormalization(std::size_t x);
  std::pair<std::size_t, std::size_t> Normalize(std::size_t x,
                                                std::size_t y);

 private:
  Vector<Vector<T>> data_;
  std::int16_t x_norm;
  std::int16_t y_norm;

  inline void ExtendRight(std::size_t size);
  inline void ExtendLeft(std::size_t size);
  inline void ExtendUp(std::size_t size);
  inline void ExtendDown(std::size_t size);
};
}  // namespace utils
#include "matrix.tpp"
