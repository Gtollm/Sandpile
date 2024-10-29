#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <utility>

#include "lib/vector/vector.hpp"
#include "matrix.hpp"

namespace utils {

template <typename T>
Matrix<T>::Matrix() : x_norm(0), y_norm(0) {}

template <typename T>
Matrix<T>::Matrix(std::size_t height, std::size_t width) {
  this->data_.resize(height);
  for (std::size_t y = 0; y < height; ++y) {
    this->data_[y].resize(width);
  }
}

template <typename T>
Matrix<T>::Matrix(
    const std::initializer_list<std::initializer_list<T>>& data) {
  for (std::size_t y = 0; y < data.size(); ++y) {
    for (std::size_t x = 0; x < data.size(); ++x) {
      this->data_[y][x] = (data.begin() + sizeof(data[y]) * y + x);
    }
  }
}

template <typename T>
Matrix<T>::Matrix(const Vector<Vector<T>>& data) : data_(data) {}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& obj) {
  this->clear();
  this->data_ = obj.data_;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(
    const std::initializer_list<std::initializer_list<T>>& data) {
  this->clear();
  for (std::size_t y = 0; y < data.size(); ++y) {
    for (std::size_t x = 0; x < data.size(); ++x) {
      this->data_[y][x] = (data.begin() + sizeof(data[y]) * y + x);
    }
  }
}

template <typename T>
Matrix<T>::~Matrix() {}

template <typename T>
void Matrix<T>::Extend(Direction dr, std::size_t size) {
  switch (dr) {
    case Direction::DOWN:
      ExtendDown(size);
      break;
    case Direction::UP:
      ExtendUp(size);
      break;
    case Direction::RIGHT:
      ExtendRight(size);
      break;
    case Direction::LEFT:
      ExtendLeft(size);
      break;
    case Direction::ALL:
      ExtendLeft(size);
      ExtendRight(size);
      ExtendDown(size);
      ExtendUp(size);
      break;
  }
}

template <typename T>
Vector<T>& Matrix<T>::operator[](std::size_t row) {
  return this->data_[row];
}

template <typename T>
const Vector<T>& Matrix<T>::operator[](std::size_t row) const {
  return this->data_[row];
}

template <typename T>
void Matrix<T>::clear() {
  this->data_.clear();
}

template <typename T>
Vector<T> Matrix<T>::GetRow(std::size_t row) const {
  return this->data_[row];
}

template <typename T>
Vector<T> Matrix<T>::GetCollumn(std::size_t collumn) const {
  Vector<T> res;
  for (std::size_t j = 0; j < this->data_[collumn].size(); ++j) {
    res[j] = this->data_[j][collumn];
  }
  return res;
}

template <typename T>
T Matrix<T>::GetElement(std::size_t row, std::size_t collumn) const {
  return this->data_[row][collumn];
}

template <typename T>
std::size_t Matrix<T>::GetWidth() const {
  if (!this->data_.empty()) {
    return this->data_[0].size();
  }
  return 0;
}

template <typename T>
std::size_t Matrix<T>::GetHeight() const {
  return this->data_.size();
}

template <typename T>
std::pair<std::size_t, std::size_t> Matrix<T>::GetNormalization() const {
  return {this->x_norm, this->y_norm};
}

template <typename T>
std::int16_t Matrix<T>::GetXNormalized(std::int16_t x) const {
  return x + this->x_norm;
}

template <typename T>
std::int16_t Matrix<T>::GetYNormalized(std::int16_t y) const {
  return y + this->y_norm;
}

template <typename T>
T& Matrix<T>::at(std::size_t row, std::size_t collumn) {
  return this->data_[row][collumn];
}

template <typename T>
const T& Matrix<T>::at(std::size_t row, std::size_t collumn) const {
  return this->data_[row][collumn];
}

template <typename T>
void Matrix<T>::set(std::size_t row, std::size_t collumn, const T& val) {
  this->data_[row][collumn] = val;
}

template <typename T>
void Matrix<T>::SetElement(std::size_t urow, std::size_t collumn,
                           const T& val) {
  this->data_[urow + this->y_norm][collumn + this->x_norm] = val;
}

template <typename T>
void Matrix<T>::SetUElement(std::int16_t urow, std::int16_t collumn,
                            const T& val) {
  this->data_[urow + this->y_norm][collumn + this->x_norm] = val;
}

template <typename T>
void Matrix<T>::SetRow(std::size_t row, const T& val) {
  this->data_[row] = val;
}

template <typename T>
void Matrix<T>::SetNormalization(std::size_t x, std::size_t y) {
  this->x_norm = x;
  this->y_norm = y;
}

template <typename T>
void Matrix<T>::SetXNormalization(std::size_t x) {
  this->x_norm = x;
}

template <typename T>
void Matrix<T>::SetYNormalization(std::size_t y) {
  this->y_norm = y;
}

template <typename T>
std::pair<std::size_t, std::size_t> Matrix<T>::Normalize(std::size_t x,
                                                         std::size_t y) {
  return {x + x_norm, y + y_norm};
}

template <typename T>
inline void Matrix<T>::ExtendRight(std::size_t size) {
  for (int i = 0; i < this->data_.size(); ++i) {
    this->data_[i].resize(this->data_[i].size() + size);
  }
}

template <typename T>
inline void Matrix<T>::ExtendUp(std::size_t size) {
  this->y_norm += size;
  this->data_.resize(
      this->data_.size() + size,
      utils::Vector<T>(this->data_.size() > 0 ? this->data_[0].size() : 0));
  std::rotate(this->data_.begin(), this->data_.end() - size,
              this->data_.end());
}

template <typename T>
inline void Matrix<T>::ExtendLeft(std::size_t size) {
  this->x_norm += size;
  for (int i = 0; i < this->data_.size(); ++i) {
    this->data_[i].resize(this->data_[i].size() + size);
    std::rotate(this->data_[i].begin(), this->data_[i].end() - size,
                this->data_[i].end());
  }
}

template <typename T>
inline void Matrix<T>::ExtendDown(std::size_t size) {
  this->data_.resize(
      this->data_.size() + size,
      utils::Vector<T>(this->data_.size() > 0 ? this->data_[0].size() : 0));
}

}  // namespace utils
