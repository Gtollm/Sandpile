#include <cstddef>
#include <limits>
#include <stdexcept>

#include "lib/linked_list/linked_list.hpp"

namespace utils {

template <typename T>
LinkedList<T>::LinkedList() : head_(nullptr), tail_(nullptr), size_(0) {}

template <typename T>
T LinkedList<T>::Get(const std::size_t index) {
  if (index < 0) {
    throw std::out_of_range("Index out of range");
  }

  Node* current = this->head_;
  std::size_t count = 0;

  while (current != nullptr) {
    if (count == index) {
      return current->data;
    }
    current = current->next_;
    count++;
  }
  throw std::out_of_range("Index out of range");
}

template <typename T>
std::size_t LinkedList<T>::Size() const {
  return this->size_;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Search(const T& element) {
  Node* current = this->head_;

  while (current != nullptr) {
    if (current->data == element) {
      return current;
    }
    current = current->next_;
  }

  return nullptr;
}

template <typename T>
void LinkedList<T>::Insert(const T& num, const std::size_t index) {
  Node* newNode = new Node{num, nullptr};
  ++this->size_;

  if (index == 0) {
    newNode->next_ = this->head_;
    this->head_ = newNode;
    if (this->tail_ == nullptr) {
      this->tail_ = newNode;
    }
    return;
  }

  Node* temp = this->head_;
  for (std::size_t i = 0; i < index - 1 && temp; ++i) {
    temp = temp->next_;
  }

  if (!temp) {
    delete newNode;
    return;
  }

  newNode->next_ = temp->next_;
  temp->next_ = newNode;

  if (newNode->next_ == nullptr) {
    this->tail_ = newNode;
  }
}

template <typename T>
void LinkedList<T>::Delete(std::size_t index) {
  if (head_ == nullptr) return;
  --this->size_;
  if (index == 0) {
    Node* temp = head_;
    this->head_ = this->head_->next_;
    delete temp;
    if (this->head_ == nullptr) {
      tail_ = nullptr;
    }
    return;
  }

  Node* temp = this->head_;
  for (std::size_t i = 0; i < index - 1 && temp; ++i) {
    temp = temp->next_;
  }

  if (!temp || !temp->next_) return;
  Node* nodeToDelete = temp->next_;
  temp->next_ = temp->next_->next_;

  if (temp->next_ == nullptr) {
    this->tail_ = temp;
  }

  delete nodeToDelete;
}

template <typename T>
T LinkedList<T>::Minimum() {
  if (this->head_ == nullptr) throw std::runtime_error("List is empty");

  T mn = std::numeric_limits<T>::max();
  Node* current = this->head_;

  while (current != nullptr) {
    if (current->data < mn) {
      mn = current->data;
    }
    current = current->next_;
  }
  return mn;
}

template <typename T>
T LinkedList<T>::Maximum() {
  if (this->head_ == nullptr) throw std::runtime_error("List is empty");

  T mx = std::numeric_limits<T>::min();
  Node* current = this->head_;

  while (current != nullptr) {
    if (current->data > mx) {
      mx = current->data;
    }
    current = current->next_;
  }
  return mx;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Successor(const T& element) {
  Node* current = Search(element);
  if (current && current->next_) {
    return current->next_;
  }
  return nullptr;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Predecessor(const T& element) {
  Node* current = head_;
  Node* prev = nullptr;

  while (current != nullptr) {
    if (current->data == element) {
      return prev;
    }
    prev = current;
    current = current->next_;
  }
  return nullptr;
}

template <typename T>
LinkedList<T>::~LinkedList() {
  while (this->head_ != nullptr) {
    Node* temp = this->head_;
    this->head_ = this->head_->next_;
    delete temp;
  }
  this->tail_ = nullptr;
}

template <typename T>
T& LinkedList<T>::front() {
  if (this->head_ == nullptr) {
    throw std::runtime_error("List is empty");
  }
  return this->head_->data;
}

template <typename T>
const T& LinkedList<T>::front() const {
  if (this->head_ == nullptr) {
    throw std::runtime_error("List is empty");
  }
  return this->head_->data;
}

template <typename T>
T& LinkedList<T>::back() {
  if (this->tail_ == nullptr) {
    throw std::runtime_error("List is empty");
  }
  return this->tail_->data;
}

template <typename T>
const T& LinkedList<T>::back() const {
  if (this->tail_ == nullptr) {
    throw std::runtime_error("List is empty");
  }
  return this->tail_->data;
}

template <typename T>
void LinkedList<T>::push_back(const T& value) {
  Node* new_node = new Node{value, nullptr};
  ++this->size_;
  if (this->tail_) {
    this->tail_->next_ = new_node;
  } else {
    this->head_ = new_node;
  }
  this->tail_ = new_node;
}

template <typename T>
void LinkedList<T>::push_front(const T& value) {
  Node* new_node = new Node{value, head_};
  ++this->size_;
  head_ = new_node;
  if (this->tail_ == nullptr) {
    this->tail_ = new_node;
  }
}

template <typename T>
T LinkedList<T>::pop_back() {
  if (this->head_ == nullptr) {
    throw std::runtime_error("List is empty");
  }
  --this->size_;
  if (this->head_ == this->tail_) {
    T data = this->head_->data;
    delete this->head_;
    this->head_ = nullptr;
    this->tail_ = nullptr;
    return data;
  }

  Node* current = this->head_;
  while (current->next_ != this->tail_) {
    current = current->next_;
  }

  T data = this->tail_->data;
  delete this->tail_;
  this->tail_ = current;
  this->tail_->next_ = nullptr;
  return data;
}

template <typename T>
T LinkedList<T>::pop_front() {
  if (this->head_ == nullptr) {
    throw std::runtime_error("List is empty");
  }
  --this->size_;
  T data = this->head_->data;
  Node* temp = this->head_;
  this->head_ = this->head_->next_;
  delete temp;
  if (this->head_ == nullptr) {
    this->tail_ = nullptr;
  }
  return data;
}

template <typename T>
LinkedList<T>::Iterator::Iterator(Node* node) : current_(node) {}

template <typename T>
bool LinkedList<T>::Iterator::operator!=(const Iterator& other) const {
  return current_ != other.current_;
}

template <typename T>
T& LinkedList<T>::Iterator::operator*() {
  return current_->data;
}

template <typename T>
T* LinkedList<T>::Iterator::operator->() {
  return current_->data;
}

template <typename T>
LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator++() {
  current_ = current_->next_;
  return *this;
}

template <typename T>
LinkedList<T>::Iterator LinkedList<T>::begin() {
  return Iterator(head_);
}

template <typename T>
LinkedList<T>::Iterator LinkedList<T>::end() {
  return Iterator(tail_);
}

template <typename T>
const LinkedList<T>::Iterator LinkedList<T>::begin() const {
  return Iterator(head_);
}

template <typename T>
const LinkedList<T>::Iterator LinkedList<T>::end() const {
  return Iterator(tail_);
}

template <typename T>
const LinkedList<T>::Iterator LinkedList<T>::cbegin() const {
  return Iterator(head_);
}

template <typename T>
const LinkedList<T>::Iterator LinkedList<T>::cend() const {
  return Iterator(tail_);
}

}  // namespace utils
