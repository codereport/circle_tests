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

FetchContent_MakeAvailable(range-v3)

# ------------------------------------------------------------------------------


set(CMAKE_CXX_COMPILER "/home/cph/circle/circle")
set(CMAKE_BUILD_RPATH "/home/cph/gcc-13.1.0/lib64/")

project(test
  LANGUAGES CXX
  VERSION 1.0.0
)

add_executable(test main.cpp)
target_compile_options(test PUBLIC -std=c++2b -gcc-toolchain=/home/cph/gcc-13.1.0)
include_directories("/home/cph/circle/")

target_link_libraries(test
  PRIVATE range-v3
  PRIVATE fmt
)
