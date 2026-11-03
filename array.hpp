#include <iostream>
#include <utility>

template <typename T, std::size_t N>
class Array final {
  using ValueType = T;

  // Default Constructor
  Array() {
    //
  }

  // Copy Constructor
  Array(const Array&) {
    //
  }

  Array(Array&&) noexcept {
    //
  }

 private:
  std::size_t size;
};