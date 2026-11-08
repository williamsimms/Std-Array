cmake_minimum_required(VERSION 3.20)

set(CMAKE_C_COMPILER clang)
set(CMAKE_C_STANDARD 23)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(ClangStarter C CXX)

# Warning sets - now actually used
set(CLANG_WARNINGS 
  -Wall -Wextra -Wpedantic
  -Wshadow -Wconversion -Wsign-conversion
  -Wdouble-promotion -Wformat=2 -Wformat-security
  -Wundef -Wvla -Wnull-dereference
  -Wimplicit-fallthrough -Wcast-qual -Wunused
  -Werror=implicit-function-declaration
)

set(CLANG_DEBUG -g3 -O0 -fno-omit-frame-pointer 
  -fstack-protector-strong
  -fsanitize=address,undefined,leak -fno-sanitize-recover=all
)

set(CLANG_RELEASE -O3 -DNDEBUG -flto -march=native)

add_compile_options(${CLANG_WARNINGS})
add_compile_options($<$<CONFIG:Debug>:${CLANG_DEBUG}>)
add_compile_options($<$<CONFIG:Release>:${CLANG_RELEASE}>)
add_link_options($<$<CONFIG:Debug>:-fsanitize=address,undefined,leak>)
add_link_options($<$<CONFIG:Release>:-flto>)

add_executable(main src/main.cpp)

add_subdirectory(Catch2)
# --- Your Array tests ---
add_executable(tests tests/array.test.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
# Make sure tests also get C++23 (they will inherit it, but be explicit)
target_compile_features(tests PRIVATE cxx_std_23)