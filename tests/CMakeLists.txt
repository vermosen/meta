
# set a folder for output
set(TEST_FILE_DIR "${CMAKE_BINARY_DIR}/test-out")
file(MAKE_DIRECTORY ${TEST_FILE_DIR})
message(STATUS "added test output directory in ${TEST_FILE_DIR}")

add_subdirectory(cpuclock)