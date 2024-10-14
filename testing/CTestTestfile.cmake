# CMake generated Testfile for 
# Source directory: D:/Decoder/testing
# Build directory: D:/Decoder/testing
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(tests "D:/Decoder/bin/Debug/tests.exe")
  set_tests_properties(tests PROPERTIES  _BACKTRACE_TRIPLES "D:/Decoder/testing/CMakeLists.txt;27;add_test;D:/Decoder/testing/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(tests "D:/Decoder/bin/Release/tests.exe")
  set_tests_properties(tests PROPERTIES  _BACKTRACE_TRIPLES "D:/Decoder/testing/CMakeLists.txt;27;add_test;D:/Decoder/testing/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(tests "D:/Decoder/bin/MinSizeRel/tests.exe")
  set_tests_properties(tests PROPERTIES  _BACKTRACE_TRIPLES "D:/Decoder/testing/CMakeLists.txt;27;add_test;D:/Decoder/testing/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(tests "D:/Decoder/bin/RelWithDebInfo/tests.exe")
  set_tests_properties(tests PROPERTIES  _BACKTRACE_TRIPLES "D:/Decoder/testing/CMakeLists.txt;27;add_test;D:/Decoder/testing/CMakeLists.txt;0;")
else()
  add_test(tests NOT_AVAILABLE)
endif()
subdirs("gtest")
