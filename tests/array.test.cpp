#define CATCH_CONFIG_MAIN
#include "../src/array.hpp"
#include "../catch.hpp"

// ============================================================
// Capacity - still PascalCase in your Array
// ============================================================
TEST_CASE("Size / Length / MaxSize / Empty") {
  Array<int, 3> a = {1, 2, 3};
  REQUIRE(a.Size() == 3);
  REQUIRE(a.Length() == 3);
  REQUIRE(a.MaxSize() == 3);
  REQUIRE(a.Empty() == false);

  Array<int, 0> e{};
  REQUIRE(e.Size() == 0);
  REQUIRE(e.Empty() == true);

  const Array<int, 3> ca = {1, 2, 3};
  REQUIRE(ca.Size() == 3);
}

// ============================================================
// Data / At / operator[] / Front / Back - still PascalCase
// ============================================================
TEST_CASE("Data") {
  Array<int, 3> a = {10, 20, 30};
  int* p = a.Data();
  REQUIRE(p[0] == 10);
  REQUIRE(p[1] == 20);
  REQUIRE(p[2] == 30);
  REQUIRE(p == &a[0]);
  p[1] = 99;
  REQUIRE(a[1] == 99);

  const Array<int, 3> ca = {1, 2, 3};
  REQUIRE(ca.Data()[0] == 1);
  REQUIRE(ca.Data()[2] == 3);
}

TEST_CASE("At") {
  Array<int, 3> a = {1, 2, 3};
  REQUIRE(a.At(0) == 1);
  REQUIRE(a.At(2) == 3);
  a.At(0) = 10;
  REQUIRE(a[0] == 10);

  const Array<int, 3> ca = {4, 5, 6};
  REQUIRE(ca.At(0) == 4);
  REQUIRE_THROWS_AS(a.At(3), std::out_of_range);
  REQUIRE_THROWS_AS(a.At(100), std::out_of_range);
  REQUIRE_THROWS_AS(ca.At(3), std::out_of_range);
}

TEST_CASE("operator[]") {
  Array<int, 3> a = {1, 2, 3};
  REQUIRE(a[0] == 1);
  a[1] = 99;
  REQUIRE(a[1] == 99);

  const Array<int, 3> ca = {7, 8, 9};
  REQUIRE(ca[0] == 7);
  REQUIRE(ca[2] == 9);
}

TEST_CASE("Front / Back") {
  Array<int, 3> a = {1, 2, 3};
  REQUIRE(a.Front() == 1);
  REQUIRE(a.Back() == 3);
  a.Front() = 10;
  a.Back() = 30;
  REQUIRE(a[0] == 10);
  REQUIRE(a[2] == 30);

  const Array<int, 3> ca = {4, 5, 6};
  REQUIRE(ca.Front() == 4);
  REQUIRE(ca.Back() == 6);

  Array<int, 1> single = {42};
  REQUIRE(single.Front() == 42);
  REQUIRE(single.Back() == 42);
}

// ============================================================
// Iterators - NOW LOWERCASE (from your screenshot)
// ============================================================
TEST_CASE("begin / end") {
  Array<int, 3> a = {1, 2, 3};
  REQUIRE(*a.begin() == 1);
  REQUIRE(*(a.end() - 1) == 3);
  REQUIRE(a.end() - a.begin() == 3);

  int expected = 1;
  for (auto it = a.begin(); it != a.end(); ++it) {
    REQUIRE(*it == expected);
    ++expected;
  }

  // modify via iterator
  for (auto it = a.begin(); it != a.end(); ++it)
    *it += 10;
  REQUIRE(a[0] == 11);
  REQUIRE(a[2] == 13);

  // const begin/end
  const Array<int, 3> ca = {4, 5, 6};
  REQUIRE(*ca.begin() == 4);
  REQUIRE(*(ca.end() - 1) == 6);
}

TEST_CASE("cbegin / cend") {
  Array<int, 3> a = {1, 2, 3};
  REQUIRE(*a.cbegin() == 1);
  REQUIRE(*(a.cend() - 1) == 3);
  REQUIRE(a.cend() - a.cbegin() == 3);

  const Array<int, 3> ca = {4, 5, 6};
  REQUIRE(*ca.cbegin() == 4);
  REQUIRE(*(ca.cend() - 1) == 6);

  int sum = 0;
  for (auto it = ca.cbegin(); it != ca.cend(); ++it)
    sum += *it;
  REQUIRE(sum == 15);
}

TEST_CASE("range-for - this is what was failing before") {
  Array<int, 3> a = {1, 2, 3};
  int sum = 0;
  for (auto x : a)
    sum += x;
  REQUIRE(sum == 6);

  // range-for with const
  const Array<int, 3> ca = {1, 2, 3};
  int csum = 0;
  for (auto x : ca)
    csum += x;
  REQUIRE(csum == 6);

  // range-for modify
  for (auto& x : a)
    x *= 2;
  REQUIRE(a[0] == 2);
  REQUIRE(a[2] == 6);
}

TEST_CASE("rbegin / rend") {
  Array<int, 3> a = {1, 2, 3};
  REQUIRE(*a.rbegin() == 3);
  REQUIRE(a.rend() - a.rbegin() == 3);

  int expected = 3;
  for (auto it = a.rbegin(); it != a.rend(); ++it) {
    REQUIRE(*it == expected);
    --expected;
  }

  for (auto it = a.rbegin(); it != a.rend(); ++it)
    *it += 100;
  REQUIRE(a[0] == 101);
  REQUIRE(a[2] == 103);

  const Array<int, 3> ca = {4, 5, 6};
  REQUIRE(*ca.rbegin() == 6);
  REQUIRE(ca.rend() - ca.rbegin() == 3);
}

TEST_CASE("crbegin / crend") {
  Array<int, 3> a = {1, 2, 3};
  REQUIRE(*a.crbegin() == 3);
  REQUIRE(a.crend() - a.crbegin() == 3);

  const Array<int, 3> ca = {4, 5, 6};
  REQUIRE(*ca.crbegin() == 6);
  REQUIRE(ca.crend() - ca.crbegin() == 3);

  int expected = 6;
  for (auto it = ca.crbegin(); it != ca.crend(); ++it) {
    REQUIRE(*it == expected);
    --expected;
  }
}

// ============================================================
// Fill / Swap / == / !=
// ============================================================
TEST_CASE("Fill") {
  Array<int, 3> a = {1, 2, 3};
  a.Fill(0);
  REQUIRE(a[0] == 0);
  REQUIRE(a[2] == 0);
  a.Fill(7);
  REQUIRE(a[1] == 7);

  Array<int, 0> e{};
  e.Fill(5);
  REQUIRE(e.Empty() == true);
}

TEST_CASE("Swap") {
  Array<int, 3> a = {1, 2, 3};
  Array<int, 3> b = {4, 5, 6};
  a.Swap(b);
  REQUIRE(a[0] == 4);
  REQUIRE(b[0] == 1);

  Array<int, 3> c = {1, 1, 1};
  Array<int, 3> d = {2, 2, 2};
  Swap(c, d);
  REQUIRE(c[0] == 2);
  REQUIRE(d[0] == 1);
}

TEST_CASE("operator== / operator!=") {
  Array<int, 3> a = {1, 2, 3};
  Array<int, 3> b = {1, 2, 3};
  Array<int, 3> c = {1, 2, 4};
  REQUIRE(a == b);
  REQUIRE_FALSE(a == c);
  REQUIRE(a != c);
  REQUIRE_FALSE(a != b);

  Array<int, 0> e1{};
  Array<int, 0> e2{};
  REQUIRE(e1 == e2);
}

TEST_CASE("Aggregate init / copy") {
  Array<int, 3> a = {1, 2, 3};
  Array<int, 3> b = a;
  REQUIRE(b == a);
  Array<int, 3> c;
  c = a;
  REQUIRE(c == a);
  Array<int, 3> d{{4, 5, 6}};
  REQUIRE(d[0] == 4);
  Array<int, 3> e{};
  REQUIRE(e[0] == 0);
}
