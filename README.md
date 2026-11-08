# Array - Custom std::array Implementation

A from-scratch implementation of `std::array<T, N>` in C++ for learning purposes. Zero-overhead, constexpr

`std::array` is deceptively simple. It is `T[N]` but with value semantics, iterators, bounds-checking, and aggregate initialization. Re-implementing it teaches you aggregates, constexpr, iterators, noexcept, and reverse iterators. No need for constructors or iterator classes.

### Features

Data Members

```cpp
ValueType data[N];
```

- Aggregate-compatible (no user declared constructors in correct version)
- `constexpr` everywhere

- Full element access: `At()`, `operator[]`, `Front()`, `Back()`, `Data()`

- Full iterators: `begin/end`, `cbegin/cend`, `rbegin/rend`, `crbegin/crend`

- Capacity: `size()`, `max_size()`, `empty()`

- Modifiers: `fill()`, `swap()`

- Non-member: `operator==`,, `std::swap`, tuple interface

#### Type aliases

```cpp
ValueType
PointerType
ReferenceType

ConstType
ConstReference
ConstPointer

Iterator
Const Iterator
Reverse Iterator
ConstReverseIterator
```

`std::array` is an aggregate. No constructors.

```cpp
template<typename T, size_t N>
struct arr {
    T elems[N];
};
```

Compiler implicitly generates:

- `constexpr arr() = default;` // default-initializes (uninitialized for POD)
- `constexpr arr(const arr&) = default;`
- `constexpr arr(arr&&) = default;`
- `constexpr arr& operator=(const arr&) = default;`
- `constexpr arr& operator=(arr&&) = default;`
- `constexpr ~arr() = default;`

### Methods

```cpp
// Capacity
constexpr bool Empty() const noexcept;
constexpr size_type Size() const noexcept;
constexpr size_type Length() const noexcept;
constexpr size_type MaxSize() const noexcept;

// Pointer to Data
PointerType Data() noexcept;
ConstPointerType Data() const noexcept;

// Element access
ReferenceType At(SizeType); //  Bounds Checked -> throws std::out_of_range
ConstReferenceType At(SizeType) const; // Bounds Checked -> throws std::out_of_range
ReferenceType operator[](SizeType);
ConstReferenceType operator[](SizeType) const;
ReferenceType Front();
ConstReferenceType Front() const;
ReferenceType Back();
ConstReferenceType Back() const;

// Iterators
IteratorType begin() noexcept;
const_iterator begin() const noexcept;
ConstIteratorType cbegin() const noexcept;

iterator end() noexcept;
const_iterator end() const noexcept;
const_iterator cend() const noexcept;

ReverseIteratorType rbegin() noexcept;
const_reverse_iterator rbegin() const noexcept;
const_reverse_iterator crbegin() const noexcept;

reverse_iterator rend() noexcept;
const_reverse_iterator rend() const noexcept;
const_reverse_iterator crend() const noexcept;

// Operations
void Fill(const T& value);
void Swap(arr& other) noexcept;
```

#### Non-member

```cpp
operator==,
operator!=,
Swap(arr&, arr&)
```
