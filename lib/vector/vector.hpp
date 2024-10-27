#pragma once

#include <cstddef>

template <typename T>
class Vector {
 public:
  // Constructors / Destructor
  Vector();
  explicit Vector(std::size_t size);
  Vector(const Vector& obj);
  Vector<T>& operator=(const Vector<T>& obj);
  ~Vector();
  // Iterators:
  class Iterator {
   public:
    Iterator(T* obj);
    Iterator& operator++();
    Iterator& operator--();
    T& operator*();
    bool operator==(const Iterator& obj) const;
    bool operator!=(const Iterator& obj) const;
    template <class InputIterator>
    static std::size_t distance(const InputIterator& begin,
                                const InputIterator& end);

   private:
    T* current_;
  };
  template <class InputIterator>
  Vector(const InputIterator& begin, const InputIterator& end);
  Iterator begin();
  const Iterator begin() const;
  Iterator end();
  const Iterator end() const;
  const Iterator cbegin() const;
  const Iterator cend() const;
  // Capacity:
  std::size_t size() const;
  std::size_t max_size() const;
  void resize(std::size_t size, const T& val = T());
  std::size_t capacity() const;
  bool empty() const;
  void reserve(std::size_t malloc);
  void shrink_to_fit();
  // Element access:
  T& operator[](std::size_t i);
  const T& operator[](std::size_t i) const;
  T& at(std::size_t n);
  const T& at(std::size_t n) const;
  T& front();
  const T& front() const;
  T& back();
  const T& back() const;
  T* data();
  const T* data() const;
  // Modifiers:
  template <class InputIterator>
  void assign(InputIterator begin, InputIterator end);
  void assign(std::size_t size, const T& val);
  void clear();
  void push_back(const T& obj);
  void pop_back();
  Iterator erase(const Iterator position);
  Iterator erase(const Iterator begin, const Iterator end);
  Iterator insert(const Iterator position, const T& val);

  void swap(Vector& obj);

 private:
  std::size_t size_;
  T* data_;
  std::size_t capacity_;
};

#include "vector.tpp"
