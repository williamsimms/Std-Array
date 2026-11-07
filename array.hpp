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

  // Data Members
  SizeType size{N};
  ValueType data[N];

  // Length and Size
  [[nodiscard]] constexpr SizeType Size() const noexcept { return this->size; }
  [[nodiscard]] constexpr SizeType Length() const noexcept {
    return this->size;
  }
  [[nodiscard]] constexpr bool Empty() const noexcept { return size == 0; }
  [[nodiscard]] constexpr SizeType MaxSize() const noexcept { return N; }

  // Return Pointer to Data
  PointerType Data() noexcept { return this->data; }
  ConstPointerType Data() const noexcept { return this->data; }

  // Bounds Checked Element Access
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

  [[nodiscard]] ConstReferenceType operator[](SizeType index) const noexcept {
    return data[index];
  }

  [[nodiscard]] ReferenceType operator[](SizeType index) noexcept {
    return data[index];
  }

  [[nodiscard]] ReferenceType Front() { return data[0]; }
  [[nodiscard]] ConstReferenceType Front() const { return data[0]; }

  [[nodiscard]] ReferenceType Back() { return data[size - 1]; }
  [[nodiscard]] ConstReferenceType Back() const { return data[size - 1]; }

  // Iterators
  IteratorType Begin() noexcept {
    //
  }

  ConstIteratorType Begin() const noexcept {
    //
  }

  ConstIteratorType CBegin() const noexcept {
    //
  }

  IteratorType End() noexcept {
    //
  }

  ConstIteratorType End() const noexcept {
    //
  }

  ConstIteratorType CEnd() const noexcept {
    //
  }

  IteratorType RBegin() noexcept {
    //
  }

  ConstIteratorType RBegin() const noexcept {
    //
  }

  ConstIteratorType CRBegin() const noexcept {
    //
  }

  IteratorType REnd() noexcept {
    //
  }

  ConstIteratorType REnd() const noexcept {
    //
  }

  ConstIteratorType CREnd() const noexcept {
    //
  }

  void Fill(ConstReferenceType value) noexcept {
    for (SizeType i = 0; i < size; ++i) {
      data[i] = value;
    }
  }

  void Swap(Array& other) noexcept {
    for (SizeType i = 0; i < size; ++i) {
      std::swap(data[i], other.data[i]);
    }
  }
};

template <typename T, std::size_t N>
bool operator==(const Array<T, N>& lhs, const Array<T, N>& rhs) {
  for (std::size_t i = 0; i < N; ++i) {
    if (lhs[i] != rhs[i]) {
      return false;
    }
  }
  return true;
}

template <typename T, std::size_t N>
bool operator!=(const Array<T, N>& lhs, const Array<T, N>& rhs) {
  return !(lhs == rhs);
}

template <typename T, std::size_t N>
T& Get(Array<T, N>& arr, std::size_t index) {
  return arr.At(index);
}

template <typename T, std::size_t N>
void Swap(Array<T, N>& lhs, Array<T, N>& rhs) {
  lhs.Swap(rhs);
}