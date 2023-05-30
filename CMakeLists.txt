cmake_minimum_required (VERSION 3.11)

include(FetchContent)

# --- Fetch fmt -----------------------------------------------------------

FetchContent_Declare(fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG 9.0.0
)

FetchContent_GetProperties(fmt)
if(NOT fmt_POPULATED)
  FetchContent_Populate(fmt)
  add_subdirectory(${fmt_SOURCE_DIR} ${fmt_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# --- Fetch range-v3 ------------------------------------------------------------

FetchContent_Declare(range-v3
  GIT_REPOSITORY https://github.com/ericniebler/range-v3
)

FetchContent_GetProperties(range-v3)
if(NOT range-v3_POPULATED)
  FetchContent_Populate(range-v3)
  add_subdirectory(${range-v3_SOURCE_DIR} ${range-v3_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# --- Fetch blackbird ------------------------------------------------------------

FetchContent_Declare(blackbird
  GIT_REPOSITORY https://github.com/codereport/blackbird.git
  GIT_TAG main
)

FetchContent_GetProperties(blackbird)
if(NOT blackbird_POPULATED)
  FetchContent_Populate(blackbird)
  add_subdirectory(${blackbird_SOURCE_DIR} ${blackbird_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# ------------------------------------------------------------------------------


set(CMAKE_CXX_COMPILER "/home/cph/circle_tests/circle")
set(CMAKE_BUILD_RPATH "/home/cph/gcc-13.1.0/lib64/")

project(test
  LANGUAGES CXX
  VERSION 1.0.0
)

add_executable(test main.cpp)
target_compile_options(test PUBLIC -std=c++2b -gcc-toolchain=/home/cph/gcc-13.1.0)
include_directories("/home/cph/circle_tests/")
include_directories(${ufo_SOURCE_DIR})
include_directories(${blackbird_SOURCE_DIR})

target_link_libraries(test
  PRIVATE range-v3
  PRIVATE fmt
)
