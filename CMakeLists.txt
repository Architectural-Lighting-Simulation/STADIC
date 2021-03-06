cmake_minimum_required(VERSION 2.8.11)

project(stadic)

if(CMAKE_COMPILER_IS_GNUCXX)
  # Apparently 4.6 is the earliest version supporting nullptr and range-based for
  # https://gcc.gnu.org/projects/cxx0x.html
  if(${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS "4.6.0")
    message(FATAL_ERROR "g++ versions earlier than 4.6.0 are not supported")
  endif()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(MSVC)
  # Visual Studio compiler check, totally borrowed from OpenStudio
  # http://en.wikipedia.org/wiki/Visual_C%2B%2B#32-bit_and_64-bit_versions
  if(${CMAKE_C_COMPILER_VERSION} VERSION_LESS "18.0.21005.1")
    message(FATAL_ERROR "Visual Studio earlier than VS2013 is not supported")
  endif()
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  # This check for clang seems to work, at least on Ubuntu. Not that much 
  # else works on Ubuntu: had to add -I/usr/include/c++/4.8/ and 
  # -I/usr/include/x86_64-linux-gnu/c++/4.8/ to get it to compile.
  # Mac works as well!
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
endif()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Boost
set(USE_INSTALLED_BOOST OFF CACHE BOOL "Look for installed Boost")
if(USE_INSTALLED_BOOST)
  find_package(Boost 1.57 REQUIRED)
else()
  include(ExternalProject)
  ExternalProject_Add(boost-geometry
    URL ${CMAKE_SOURCE_DIR}/dependencies/boost-geometry-1_57.tar.gz
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND "")
  set(Boost_INCLUDE_DIR ${CMAKE_BINARY_DIR}/boost-geometry-prefix/src/boost-geometry)
endif()
include_directories(${Boost_INCLUDE_DIR})

# JSON Dependency
include_directories("dependencies/jsoncpp")
# Add the gtest directory
add_subdirectory(dependencies/gtest-1.7.0)

add_subdirectory(lib)
add_subdirectory(utilities)
enable_testing(true)
add_subdirectory(test)
