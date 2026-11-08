# arr - Custom std::array Implementation

A from-scratch implementation of `std::array<T, N>` in C++ for learning purposes. Zero-overhead, constexpr, STL-compatible.

`std::array` is deceptively simple. It's just `T[N]` but with value semantics, iterators, bounds-checking, and aggregate initialization. Re-implementing it teaches you aggregates, constexpr, iterators, SFINAE/noexcept, and reverse iterators.

### Features

- Aggregate-compatible (no user-declared constructors in correct version)
- `constexpr` everywhere
- Full element access: `at()`, `operator[]`, `front()`, `back()`, `data()`
- Full iterators: `begin/end`, `cbegin/cend`, `rbegin/rend`, `crbegin/crend`
- Capacity: `size()`, `max_size()`, `empty()`
- Modifiers: `fill()`, `swap()`
- Non-member: `operator==`,, `std::swap`, tuple interface

````
#### Type aliases
```cpp
value_type, size_type, difference_type
reference, const_reference, pointer, const_pointer
iterator, const_iterator, reverse_iterator, const_reverse_iterator
````

#### Constructors - NONE

`std::array` is an aggregate. No constructors.

```cpp
template<typename T, size_t N>
struct arr {
    T elems[N]; // only member
};
```

Compiler implicitly generates:

- `constexpr arr() = default;` // default-initializes (uninitialized for POD)
- `constexpr arr(const arr&) = default;`
- `constexpr arr(arr&&) = default;`
- `constexpr arr& operator=(const arr&) = default;`
- `constexpr arr& operator=(arr&&) = default;`
- `constexpr ~arr() = default;`

#### Methods

```cpp
// Element access
reference at(size_type);
const_reference at(size_type) const; // throws std::out_of_range
reference operator[](size_type);
const_reference operator[](size_type) const;
reference front(); const_reference front() const;
reference back(); const_reference back() const;
pointer data() noexcept; const_pointer data() const noexcept;

// Iterators
iterator begin() noexcept; const_iterator begin() const noexcept; const_iterator cbegin() const noexcept;
iterator end() noexcept; const_iterator end() const noexcept; const_iterator cend() const noexcept;
reverse_iterator rbegin() noexcept; const_reverse_iterator rbegin() const noexcept; const_reverse_iterator crbegin() const noexcept;
reverse_iterator rend() noexcept; const_reverse_iterator rend() const noexcept; const_reverse_iterator crend() const noexcept;

// Capacity
constexpr bool empty() const noexcept;
constexpr size_type size() const noexcept;
constexpr size_type max_size() const noexcept;

// Operations
void fill(const T& value);
void swap(arr& other) noexcept(is_nothrow_swappable_v<T>);
```

#### Non-member

```cpp
get<I>(arr)
operator==, operator<=> (C++20)
swap(arr&, arr&)
tuple_size, tuple_element
```

### Usage

```cpp
#include "arr.hpp"

arr<int, 3> a = {1, 2, 3};
arr<int, 3> b{{4, 5, 6}};

a[0] = 10;
a.at(1) = 20;
a.front(); // 10
a.back();  // 3
a.data();  // int*
a.size();  // 3
a.empty(); // false

a.fill(0);
for (auto& x : a) x++;

std::sort(a.begin(), a.end());
```
