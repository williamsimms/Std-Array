#pragma once

#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <utility>

template <typename T, std::size_t N = 0>
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
  [[nodiscard]] constexpr auto Size() const noexcept -> SizeType { return N; }
  [[nodiscard]] constexpr auto Length() const noexcept -> SizeType { return N; }
  [[nodiscard]] constexpr auto Empty() const noexcept -> bool { return N == 0; }
  [[nodiscard]] constexpr auto MaxSize() const noexcept -> SizeType {
    return N;
  }

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
  IteratorType begin() noexcept { return data; }
  ConstIteratorType begin() const noexcept { return data; }
  ConstIteratorType cbegin() const noexcept { return data; }

  IteratorType end() noexcept { return data + N; }
  ConstIteratorType end() const noexcept { return data + N; }
  ConstIteratorType cend() const noexcept { return data + N; }

  ReverseIteratorType rbegin() noexcept {
    return ReverseIteratorType(this->end());
  }

  ConstReverseIteratorType rbegin() const noexcept {
    return ConstReverseIteratorType(this->end());
  }

  ConstReverseIteratorType crbegin() const noexcept {
    return ConstReverseIteratorType(this->end());
  }

  ReverseIteratorType rend() noexcept {
    return ReverseIteratorType(this->begin());
  }

  ConstReverseIteratorType rend() const noexcept {
    return ConstReverseIteratorType(this->begin());
  }

  ConstReverseIteratorType crend() const noexcept {
    return ConstReverseIteratorType(this->begin());
  }

  void Fill(ConstReferenceType value) noexcept {
    for (SizeType i = 0; i < N; ++i) {
      data[i] = value;
    }
  }

  void Swap(Array& other) noexcept {
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
auto operator!=(const Array<T, N>& lhs, const Array<T, N>& rhs) -> bool {
  return !(lhs == rhs);
}

template <typename T, std::size_t N>
void Swap(Array<T, N>& lhs, Array<T, N>& rhs) {
  lhs.Swap(rhs);
}
