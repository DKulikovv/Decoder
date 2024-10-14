cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_COMPILER "clang++")
set(Required_Icu_Version 63)

# include(FindICU)
# find_package(ICU ${Required_Icu_Version} OPTIONAL_COMPONENTS uc i18n)

#set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
#find_package(ICU 4.4 COMPONENTS io i18n REQUIRED)

#include_directories(${ICU_INCLUDE_DIRS})
include_directories(src)

add_subdirectory(external/icu-cmake)

add_library(Icu4c_decoder_lib 
  test_files/demo.cpp
  src/general_decoder.hpp
  src/icu_decoder_impl.hpp
  #src/general_decoder.cc
)

target_link_libraries(Icu4c_decoder_lib icu)