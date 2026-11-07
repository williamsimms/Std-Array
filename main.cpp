#include <iostream>
#include "array.hpp"

int main(int argc, char* argv[]) {
  std::cout << "Hello, World!" << std::endl;

  Array<int, 5> arr{1, 2, 3, 4, 5};

  return 0;
}