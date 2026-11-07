#pragma once

#include <stdexcept>

template <typename T, std::size_t N>
struct Array final {
  using ValueType = T;
  using PointerType = T*;
  using ReferenceType = T&;

  using DifferenceType = std::ptrdiff_t;

  using ConstType = const T;
  using ConstPointerType = const T*;
  using ConstReferenceType = const T&;

  using SizeType = std::size_t;

  using IteratorType = T*;
  using ConstIteratorType = const T*;
  using ReverseIteratorType = std::reverse_iterator<IteratorType>;
  using ConstReverseIteratorType = std::reverse_iterator<ConstIteratorType>;

  SizeType size{N};
  ValueType data[N];

  // Length and Size
  SizeType Size() const { return this->size; }
  SizeType Length() const { return this->size; }

  // Return Pointer to Data
  ValueType* Data() { return this->data; }

  // Element Access
  [[nodiscard]] ConstReferenceType At(SizeType index) const noexcept(false) {
    if (index >= size) {
      throw std::out_of_range("Index out of range");
    }

    if (index < 0) {
      throw std::out_of_range("Index cannot be negative");
    }

    return data[index];
  }

  [[nodiscard]] ReferenceType At(SizeType index) noexcept(false) {
    if (index >= size) {
      throw std::out_of_range("Index out of range");
    }

    if (index < 0) {
      throw std::out_of_range("Index cannot be negative");
    }

    return data[index];
  }

  [[nodiscard]] ConstReferenceType operator[](SizeType index) const {
    if (index >= size) {
      throw std::out_of_range("Index out of range");
    }

    if (index < 0) {
      throw std::out_of_range("Index cannot be negative");
    }

    return data[index];
  }

  ReferenceType Front() { return data[0]; }
  ConstReferenceType Front() const { return data[0]; }

  ReferenceType Back() { return data[size - 1]; }
  ConstReferenceType Back() const { return data[size - 1]; }

  [[nodiscard]] bool Empty() const noexcept { return size == 0; }

  void Fill(ConstReferenceType value) noexcept {
    for (SizeType i = 0; i < size; ++i) {
      data[i] = value;
    }
  }
};