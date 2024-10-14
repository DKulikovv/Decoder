if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/gtest")
  message(STATUS "Google Test not present.  Fetching from the web...")
  file(DOWNLOAD "https://github.com/google/googletest/archive/release-1.12.0.zip" ${CMAKE_CURRENT_SOURCE_DIR}/master.zip)
  execute_process(COMMAND ${CMAKE_COMMAND} -E tar x ${CMAKE_CURRENT_SOURCE_DIR}/master.zip WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
  file(REMOVE master.zip)
  file(RENAME googletest-release-1.12.0 gtest)
endif()

ADD_SUBDIRECTORY (gtest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

execute_process(COMMAND ${CMAKE_COMMAND} -E tar x ${CMAKE_CURRENT_SOURCE_DIR}/files.zip WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB SRCS *.cpp)

add_executable(tests ${SRCS})

target_link_libraries(tests
    CED_decoder_lib
    Chardet_decoder_lib
    Uchardet_decoder_lib
    Icu4c_decoder_lib
    gtest 
    gtest_main
)

add_test(NAME tests
         COMMAND tests)