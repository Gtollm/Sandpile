#pragma once
#include <cstddef>
#include <stdexcept>

namespace utils {

template <typename T>
class LinkedList {
 private:
  struct Node {
    T data;
    Node* next_;
  };
  Node* head_;
  Node* tail_;
  std::size_t size_;

 public:
  LinkedList();
  T Get(const std::size_t index);
  std::size_t Size() const;
  Node* Search(const T& element);
  void Insert(const T& num, const std::size_t index = 0);
  void Delete(std::size_t index = 0);
  T Minimum();
  T Maximum();
  Node* Successor(const T& element);
  Node* Predecessor(const T& element);
  ~LinkedList();
  T& front();
  const T& front() const;
  T& back();
  const T& back() const;
  void push_back(const T& obj);
  void push_front(const T& obj);
  T pop_back();
  T pop_front();
  class Iterator {
   public:
    Iterator(Node* node);
    bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;
    T& operator*();
    T* operator->();
    Iterator& operator++();

   private:
    Node* current_;
  };
  Iterator begin();
  const Iterator begin() const;
  const Iterator cbegin() const;
  Iterator end();
  const Iterator end() const;
  const Iterator cend() const;
};

}  // namespace utils

#include "linked_list.tpp"
