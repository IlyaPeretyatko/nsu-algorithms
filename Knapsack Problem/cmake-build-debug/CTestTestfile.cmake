# CMake generated Testfile for 
# Source directory: D:/nsu_repos/template/lab11
# Build directory: D:/nsu_repos/template/lab11/cmake-build-debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(testlab11.exe "D:/nsu_repos/template/lab11/test/testlab11.exe" "./lab11")
set_tests_properties(testlab11.exe PROPERTIES  DEPENDS "lab11" _BACKTRACE_TRIPLES "D:/nsu_repos/template/modules/test_runner.cmake;23;add_test;D:/nsu_repos/template/modules/test_runner.cmake;0;;D:/nsu_repos/template/modules/common_lab.cmake;3;include;D:/nsu_repos/template/modules/common_lab.cmake;0;;D:/nsu_repos/template/lab11/CMakeLists.txt;9;include;D:/nsu_repos/template/lab11/CMakeLists.txt;0;")
