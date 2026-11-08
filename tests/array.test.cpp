#define CATCH_CONFIG_MAIN
#include "../src/array.hpp"
#include "../catch.hpp"


// ============================================================
// Capacity
// ============================================================
TEST_CASE("Size / Length / MaxSize / Empty") {
  Array<int, 3> a = {1, 2, 3};
  REQUIRE(a.Size() == 3);
  REQUIRE(a.Length() == 3);
  REQUIRE(a.MaxSize() == 3);
  REQUIRE(a.Empty() == false);

  Array<int, 0> e{};
  REQUIRE(e.Size() == 0);
  REQUIRE(e.Length() == 0);
  REQUIRE(e.MaxSize() == 0);
  REQUIRE(e.Empty() == true);

  Array<int, 5> b{};
  REQUIRE(b.Size() == 5);
  REQUIRE(b.Empty() == false);

  const Array<int, 3> ca = {1, 2, 3};
  REQUIRE(ca.Size() == 3);
  REQUIRE(ca.Empty() == false);
}

// ============================================================
// Data
// ============================================================
TEST_CASE("Data") {
  Array<int, 3> a = {10, 20, 30};
  int* p = a.Data();
  REQUIRE(p != nullptr);
  REQUIRE(p[0] == 10);
  REQUIRE(p[1] == 20);
  REQUIRE(p[2] == 30);
  REQUIRE(p == &a[0]);

  // mutating via Data() mutates array
  p[1] = 99;
  REQUIRE(a[1] == 99);

  const Array<int, 3> ca = {1, 2, 3};
  const int* cp = ca.Data();
  REQUIRE(cp[0] == 1);
  REQUIRE(cp[2] == 3);
  REQUIRE(cp == &ca[0]);
}

// ============================================================
// At - bounds checked
// ============================================================
TEST_CASE("At") {
  Array<int, 3> a = {1, 2, 3};
  REQUIRE(a.At(0) == 1);
  REQUIRE(a.At(1) == 2);
  REQUIRE(a.At(2) == 3);

  // mutable
  a.At(0) = 10;
  REQUIRE(a[0] == 10);

  // const version
  const Array<int, 3> ca = {4, 5, 6};
  REQUIRE(ca.At(0) == 4);
  REQUIRE(ca.At(2) == 6);

  // throws
  REQUIRE_THROWS_AS(a.At(3), std::out_of_range);
  REQUIRE_THROWS_AS(a.At(100), std::out_of_range);
  REQUIRE_THROWS_AS(ca.At(3), std::out_of_range);
  REQUIRE_THROWS_AS(ca.At(999), std::out_of_range);
}

// ============================================================
// operator[]
// ============================================================
TEST_CASE("operator[]") {
  Array<int, 3> a = {1, 2, 3};
  REQUIRE(a[0] == 1);
  REQUIRE(a[1] == 2);
  REQUIRE(a[2] == 3);

  a[1] = 99;
  REQUIRE(a[1] == 99);

  const Array<int, 3> ca = {7, 8, 9};
  REQUIRE(ca[0] == 7);
  REQUIRE(ca[1] == 8);
  REQUIRE(ca[2] == 9);
  // ca[0] = 1; // should NOT compile - const
}

// ============================================================
// Front / Back
// ============================================================
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
// Begin / End / CBegin / CEnd
// ============================================================
TEST_CASE("Begin / End") {
  Array<int, 3> a = {1, 2, 3};

  REQUIRE(*a.Begin() == 1);
  REQUIRE(*(a.End() - 1) == 3);
  REQUIRE(a.End() - a.Begin() == 3);

  // iterate forward
  int expected = 1;
  for (auto it = a.Begin(); it != a.End(); ++it) {
    REQUIRE(*it == expected);
    ++expected;
  }

  // range-for uses Begin/End
  int sum = 0;
  for (auto x : a)
    sum += x;
  REQUIRE(sum == 6);

  // modify via iterator
  for (auto it = a.Begin(); it != a.End(); ++it)
    *it += 10;
  REQUIRE(a[0] == 11);
  REQUIRE(a[2] == 13);
}

TEST_CASE("CBegin / CEnd") {
  Array<int, 3> a = {1, 2, 3};
  REQUIRE(*a.CBegin() == 1);
  REQUIRE(*(a.CEnd() - 1) == 3);
  REQUIRE(a.CEnd() - a.CBegin() == 3);

  const Array<int, 3> ca = {4, 5, 6};
  REQUIRE(*ca.Begin() == 4);
  REQUIRE(*ca.CBegin() == 4);
  REQUIRE(*(ca.CEnd() - 1) == 6);

  int sum = 0;
  for (auto it = ca.CBegin(); it != ca.CEnd(); ++it)
    sum += *it;
  REQUIRE(sum == 15);
}

// ============================================================
// RBegin / REnd / CRBegin / CREnd
// ============================================================
TEST_CASE("RBegin / REnd") {
  Array<int, 3> a = {1, 2, 3};
  REQUIRE(*a.RBegin() == 3);
  REQUIRE(*(a.REnd() - 1) == 1);  // REnd-1 is first element in reverse order

  // iterate reverse: 3,2,1
  int expected = 3;
  for (auto it = a.RBegin(); it != a.REnd(); ++it) {
    REQUIRE(*it == expected);
    --expected;
  }

  // modify via reverse iterator
  for (auto it = a.RBegin(); it != a.REnd(); ++it)
    *it += 100;
  REQUIRE(a[0] == 101);
  REQUIRE(a[2] == 103);
}

TEST_CASE("CRBegin / CREnd") {
  Array<int, 3> a = {1, 2, 3};
  REQUIRE(*a.CRBegin() == 3);
  REQUIRE(a.CREnd() - a.CRBegin() == 3);

  const Array<int, 3> ca = {4, 5, 6};
  REQUIRE(*ca.RBegin() == 6);
  REQUIRE(*ca.CRBegin() == 6);
  // NOTE: *REnd is UB, never dereference REnd - test distance only
  REQUIRE(ca.REnd() - ca.RBegin() == 3);
  REQUIRE(ca.CREnd() - ca.CRBegin() == 3);

  // reverse iterate const
  int expected = 6;
  for (auto it = ca.CRBegin(); it != ca.CREnd(); ++it) {
    REQUIRE(*it == expected);
    --expected;
  }
}

// ============================================================
// Fill
// ============================================================
TEST_CASE("Fill") {
  Array<int, 3> a = {1, 2, 3};
  a.Fill(0);
  REQUIRE(a[0] == 0);
  REQUIRE(a[1] == 0);
  REQUIRE(a[2] == 0);

  a.Fill(7);
  REQUIRE(a[0] == 7);
  REQUIRE(a[1] == 7);
  REQUIRE(a[2] == 7);

  Array<std::string, 2> s = {"a", "b"};
  s.Fill("hi");
  REQUIRE(s[0] == "hi");
  REQUIRE(s[1] == "hi");

  Array<int, 0> e{};
  e.Fill(5);  // should not crash, does nothing
  REQUIRE(e.Empty() == true);
}

// ============================================================
// Swap - member + free function
// ============================================================
TEST_CASE("Swap member") {
  Array<int, 3> a = {1, 2, 3};
  Array<int, 3> b = {4, 5, 6};
  a.Swap(b);
  REQUIRE(a[0] == 4);
  REQUIRE(a[1] == 5);
  REQUIRE(a[2] == 6);
  REQUIRE(b[0] == 1);
  REQUIRE(b[1] == 2);
  REQUIRE(b[2] == 3);

  // swap with itself
  a.Swap(a);
  REQUIRE(a[0] == 4);
}

TEST_CASE("Swap free function") {
  Array<int, 3> a = {1, 1, 1};
  Array<int, 3> b = {2, 2, 2};
  Swap(a, b);
  REQUIRE(a[0] == 2);
  REQUIRE(b[0] == 1);

  // std::swap should also work via ADL if you call std::swap - test member swap
  // already covers logic
}

// ============================================================
// operator== / operator!=
// ============================================================
TEST_CASE("operator== / operator!=") {
  Array<int, 3> a = {1, 2, 3};
  Array<int, 3> b = {1, 2, 3};
  Array<int, 3> c = {1, 2, 4};
  Array<int, 3> d = {4, 5, 6};

  REQUIRE(a == b);
  REQUIRE_FALSE(a == c);
  REQUIRE_FALSE(a == d);
  REQUIRE(a != c);
  REQUIRE(a != d);
  REQUIRE_FALSE(a != b);

  // empty arrays are equal
  Array<int, 0> e1{};
  Array<int, 0> e2{};
  REQUIRE(e1 == e2);
  REQUIRE_FALSE(e1 != e2);
}

// ============================================================
// Aggregate init + copy
// ============================================================
TEST_CASE("Aggregate init / copy / assignment") {
  Array<int, 3> a = {1, 2, 3};
  Array<int, 3> b = a;  // copy
  REQUIRE(b == a);

  Array<int, 3> c;
  c = a;  // assign
  REQUIRE(c == a);

  Array<int, 3> d{{4, 5, 6}};  // double braces
  REQUIRE(d[0] == 4);
  REQUIRE(d[2] == 6);

  Array<int, 3> e{};
  REQUIRE(e[0] == 0);  // value-initialized to 0
}
