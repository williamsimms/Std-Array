#include "../src/array.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Array basics") {
  Array<int, 3> a = {1, 2, 3};
  REQUIRE(a.Size() == 3);
  REQUIRE(a[0] == 1);
  REQUIRE(a.Back() == 3);
  REQUIRE(a.Front() == 1);
  REQUIRE_THROWS_AS(a.At(10), std::out_of_range);
}