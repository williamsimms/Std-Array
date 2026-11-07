#include <iostream>
#include <stdexcept>

template <typename T, std::size_t N>
struct Array final {
  using ValueType = T;
  using PointerType = T*;
  using ReferenceType = T&;

  using ConstType = const T;
  using ConstPointerType = const T*;
  using ConstReferenceType = const T&;

  using SizeType = std::size_t;

  SizeType size{N};
  ValueType data[N];

  SizeType Size() const { return this->size; }

  SizeType Length() const { return this->size; }

  ValueType* Data() { return this->data; }

  ReferenceType At(SizeType index) {
    //
  }

  ConstReferenceType At(SizeType index) const {
    if (index >= size) {
      throw std::out_of_range("Index out of range");
    }

    if (index < 0) {
      throw std::out_of_range("Index cannot be negative");
    }

    return data[index];
  }

  ConstReferenceType operator[](SizeType index) const {
    if (index >= size) {
      throw std::out_of_range("Index out of range");
    }

    if (index < 0) {
      throw std::out_of_range("Index cannot be negative");
    }

    return data[index];
  }

  bool Empty() const { return size == 0; }

  void Fill(ConstReferenceType value) {
    for (SizeType i = 0; i < size; ++i) {
      data[i] = value;
    }
  }
};