# arr - Custom std::array Implementation

A from-scratch implementation of `std::array<T, N>` in C++ for learning purposes. Zero-overhead, constexpr, STL-compatible.

### Why?

`std::array` is deceptively simple. It's just `T[N]` but with value semantics, iterators, bounds-checking, and aggregate initialization. Re-implementing it teaches you aggregates, constexpr, iterators, SFINAE/noexcept, and reverse iterators.

### Features

- Aggregate-compatible (no user-declared constructors in correct version)
- `constexpr` everywhere
- Full element access: `at()`, `operator[]`, `front()`, `back()`, `data()`
- Full iterators: `begin/end`, `cbegin/cend`, `rbegin/rend`, `crbegin/crend`
- Capacity: `size()`, `max_size()`, `empty()`
- Modifiers: `fill()`, `swap()`
- Non-member: `get<I>()`, `operator==`, `operator<=>`, `std::swap`, tuple interface
- Handles `N == 0` edge case

### Project Structure

```
/include
  arr.hpp      -> your implementation
/tests
  test.cpp     -> tests
README.md
```

### API - What You Need To Implement

#### Type aliases
```cpp
value_type, size_type, difference_type
reference, const_reference, pointer, const_pointer
iterator, const_iterator, reverse_iterator, const_reverse_iterator
```

#### Constructors - NONE
`std::array` is an aggregate. Do not declare constructors.

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

### Build & Test

```bash
g++ -std=c++20 -Wall -Wextra -pedantic -Iinclude tests/test.cpp -o test
./test
```

### Implementation Checklist

- [ ] Type aliases + internal array `T elems[N]`
- [ ] `data()`, `size()`, `operator[]`
- [ ] `begin()`, `end()` -> enables range-for
- [ ] `front()`, `back()`, `at()` with bounds check
- [ ] `cbegin/cend`, `rbegin/rend`, `crbegin/crend`
- [ ] `fill()`, `empty()`, `max_size()`
- [ ] `swap()`
- [ ] Non-member `get`, comparison operators
- [ ] Test `N=0` specialization
- [ ] Make everything `constexpr` and `noexcept` where std does

### Notes on std::array quirks

1. `arr<int, 3> a;` -> elements UNINITIALIZED
2. `arr<int, 3> a{};` -> elements VALUE-INITIALIZED (zero)
3. Double braces needed: `arr<int, 3> a{{1,2,3}}` because aggregate contains array
4. `at()` throws, `operator[]` doesn't
5. No dynamic allocation

### License

MIT - Do whatever you want, it's for practice.
