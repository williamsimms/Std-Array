#pragma once
#include <cstddef>      // size_t, ptrdiff_t
#include <stdexcept>    // out_of_range
#include <type_traits>  // is_nothrow_swappable_v
#include <utility>      // std::swap

template <typename T, std::size_t N>
struct Array {
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
  ValueType data[N];

  // Capacity
  [[nodiscard]] constexpr SizeType Size() const noexcept { return N; }
  [[nodiscard]] constexpr SizeType Length() const noexcept { return N; }
  [[nodiscard]] constexpr bool Empty() const noexcept { return N == 0; }
  [[nodiscard]] constexpr SizeType MaxSize() const noexcept { return N; }

  // Pointer to Data
  [[nodiscard]] PointerType constexpr Data() noexcept { return this->data; }
  [[nodiscard]] ConstPointerType constexpr Data() const noexcept {
    return this->data;
  }

  // Element Access
  // Bounds Checked Element Access
  [[nodiscard]] ConstReferenceType At(SizeType index) const noexcept(false) {
    if (index >= N || index < 0) {
      throw std::out_of_range("Index out of range");
    }

    return data[index];
  }

  [[nodiscard]] ReferenceType At(SizeType index) noexcept(false) {
    if (index >= N || index < 0) {
      throw std::out_of_range("Index out of range");
    }

    return data[index];
  }

  // Overloaded Operator [] - Element Access Without Bounds Checking
  [[nodiscard]] ConstReferenceType operator[](SizeType index) const noexcept {
    return data[index];
  }

  [[nodiscard]] ReferenceType operator[](SizeType index) noexcept {
    return data[index];
  }

  // Front Element Access
  [[nodiscard]] ReferenceType Front() noexcept { return data[0]; }
  [[nodiscard]] ConstReferenceType Front() const noexcept { return data[0]; }

  // Back Element Access
  [[nodiscard]] ReferenceType Back() noexcept { return data[N - 1]; }
  [[nodiscard]] ConstReferenceType Back() const noexcept { return data[N - 1]; }

  // Iterators
  IteratorType Begin() noexcept { return data; }
  ConstIteratorType Begin() const noexcept { return data; }
  ConstIteratorType CBegin() const noexcept { return data; }

  IteratorType End() noexcept { return data + N; }
  ConstIteratorType End() const noexcept { return data + N; }
  ConstIteratorType CEnd() const noexcept { return data + N; }

  ReverseIteratorType RBegin() noexcept {
    return ReverseIteratorType(this->End());
  }

  ConstReverseIteratorType RBegin() const noexcept {
    return ConstReverseIteratorType(this->End());
  }

  ConstReverseIteratorType CRBegin() const noexcept {
    return ConstReverseIteratorType(this->End());
  }

  ReverseIteratorType REnd() noexcept {
    return ReverseIteratorType(this->Begin());
  }

  ConstReverseIteratorType REnd() const noexcept {
    return ConstReverseIteratorType(this->Begin());
  }

  ConstReverseIteratorType CREnd() const noexcept {
    return ConstReverseIteratorType(this->Begin());
  }

  void Fill(ConstReferenceType value) noexcept {
    for (SizeType i = 0; i < N; ++i) {
      data[i] = value;
    }
  }

  void Swap(Array& other) noexcept(std::is_nothrow_swappable_v<T>) {
    for (SizeType i = 0; i < N; ++i) {
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
void Swap(Array<T, N>& lhs, Array<T, N>& rhs) {
  lhs.Swap(rhs);
}
