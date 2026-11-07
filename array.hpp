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
  PointerType constexpr Data() noexcept { return this->data; }
  ConstPointerType constexpr Data() const noexcept { return this->data; }

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
  IteratorType Begin() noexcept { return data; }
  ConstIteratorType Begin() const noexcept { return data; }
  ConstIteratorType CBegin() const noexcept { return data; }

  IteratorType End() noexcept { return data + size; }
  ConstIteratorType End() const noexcept { return data + size; }
  ConstIteratorType CEnd() const noexcept { return data + size; }

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

// data[0] [1] [2] [3] [4]
// data, data + 1, data + 2, data + 3, data + 4, data + 5