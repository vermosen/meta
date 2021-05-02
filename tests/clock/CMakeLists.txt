cmake_minimum_required (VERSION 3.13)

SET(TARGET_NAME test-cpuclock)

setup_component(TARGET ${TARGET_NAME})

file(GLOB_RECURSE TARGET_HEADERS "*.h")
file(GLOB_RECURSE TARGET_SOURCES "*.cpp")

add_executable(
    ${TARGET_NAME}
    ${TARGET_HEADERS}
    ${TARGET_SOURCES}
)

target_link_libraries(
    ${TARGET_NAME}
	meta
	CONAN_PKG::gtest
	Threads::Threads
)

if (${EXTRA_TOOLING})
    message(STATUS "using iwyu from ${iwyu}")
    set_target_properties(${TARGET_NAME} PROPERTIES CXX_INCLUDE_WHAT_YOU_USE ${iwyu})
endif()

add_gtest(TARGET ${TARGET_NAME} BINARY ${TARGET_NAME})