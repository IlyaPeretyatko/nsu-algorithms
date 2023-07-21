# CMake generated Testfile for 
# Source directory: D:/nsu_repos/template/lab7
# Build directory: D:/nsu_repos/template/lab7/cmake-build-debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(testlab7.exe "D:/nsu_repos/template/lab7/test/testlab7.exe" "./lab7")
set_tests_properties(testlab7.exe PROPERTIES  DEPENDS "lab7" _BACKTRACE_TRIPLES "D:/nsu_repos/template/modules/test_runner.cmake;23;add_test;D:/nsu_repos/template/modules/test_runner.cmake;0;;D:/nsu_repos/template/modules/common_lab.cmake;3;include;D:/nsu_repos/template/modules/common_lab.cmake;0;;D:/nsu_repos/template/lab7/CMakeLists.txt;9;include;D:/nsu_repos/template/lab7/CMakeLists.txt;0;")
