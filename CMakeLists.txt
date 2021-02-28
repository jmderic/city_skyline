# only one tested
cmake_minimum_required (VERSION 3.10)

project (CitySkyline)

# The version number.
set (CITYSKYLINE_MAJOR_VERSION 0)
set (CITYSKYLINE_MINOR_VERSION 1)
set (CITYSKYLINE_PATCH_VERSION 0)
set(CITYSKYLINE_VERSION
  ${CITYSKYLINE_MAJOR_VERSION}.${CITYSKYLINE_MINOR_VERSION}.${CITYSKYLINE_PATCH_VERSION})

# basic compile standards
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# finding distrib libraries we want

# https://cmake.org/cmake/help/v3.10/module/FindBoost.html
find_package(Boost 1.65 REQUIRED COMPONENTS regex)
message("Boost include dir: ${Boost_INCLUDE_DIRS}")


## PROJECT specific

# creating the executable
set (CitySkyline_SOURCES
  City.cpp
  main.cpp
  )

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/CitySkyline_Config.hpp.in"
  "${PROJECT_BINARY_DIR}/CitySkyline_Config.hpp"
  )
 
# add the binary tree to the search path for include files
# so that we will find CitySkyline_Config.hpp
include_directories(
  "${PROJECT_BINARY_DIR}"
  "${PROJECT_SOURCE_DIR}"
  )

# applies to all targets.  Maybe what we want?
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra")

option (ASAN_ENABLED
  "Build with AddressSanitizer"
  OFF
  )

option (LSAN_ENABLED
  "Build with LeakSanitizer"
  OFF
  )

if(ASAN_ENABLED OR LSAN_ENABLED)
set (CMAKE_BUILD_TYPE Debug)
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -fno-omit-frame-pointer")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer")
endif(ASAN_ENABLED OR LSAN_ENABLED)

if(ASAN_ENABLED)
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fsanitize=address")
endif(ASAN_ENABLED)

if(LSAN_ENABLED)
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=leak")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fsanitize=leak")
endif(LSAN_ENABLED)

## TARTGET specific

add_executable(CitySkyline ${CitySkyline_SOURCES})

target_compile_options(CitySkyline PRIVATE -Werror -Wall -Wextra)

target_link_libraries(
    CitySkyline
    Boost::regex
    )
