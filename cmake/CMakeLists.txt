cmake_minimum_required (VERSION 3.13)

include_guard(GLOBAL)

message(STATUS   "\n")
message(STATUS   ":==================================:")
message(STATUS   ":setting global cmake configuration:")
message(STATUS   ":==================================:\n")

message(STATUS "*** configuration set to \"${CMAKE_BUILD_TYPE}\" ***")

# must be defined before the module get imported
set(INSTALL_BINARY_SUFFIX bin/${CMAKE_BUILD_TYPE})
set(INSTALL_LIBRARY_SUFFIX lib/${CMAKE_BUILD_TYPE})
set(INSTALL_INCLUDE_SUFFIX include)

message(DEBUG "INSTALL_BINARY_SUFFIX set to ${INSTALL_BINARY_SUFFIX}")
message(DEBUG "INSTALL_LIBRARY_SUFFIX set to ${INSTALL_LIBRARY_SUFFIX}")
message(DEBUG "INSTALL_INCLUDE_SUFFIX set to ${INSTALL_INCLUDE_SUFFIX}")

# load the utils module
include("${CMAKE_CURRENT_LIST_DIR}/module/utils.cmake")

find_conan(
    BINDIR ${CONAN_BIN_PATH}
    REQUIRES 1.12.0 
)

# enable the languages
enable_language(C CXX CUDA)

# set dialect
set(CMAKE_CXX_STANDARD ${CXX_DIALECT})

# set verbosity
if(VERBOSE)
    set(CMAKE_VERBOSE_MAKEFILE ON)
endif()

set(THREADS_PREFER_PTHREAD_FLAG ON)
message(STATUS "THREADS_PREFER_PTHREAD_FLAG value: ${THREADS_PREFER_PTHREAD_FLAG}")
FIND_PACKAGE(Threads)

# set the compiler flags
message(STATUS "CMAKE_BUILD_TYPE set to ${CMAKE_BUILD_TYPE}")

# set the PIC/PIE flag
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
message(STATUS "CMAKE_POSITION_INDEPENDENT_CODE set to ${CMAKE_POSITION_INDEPENDENT_CODE}")

# check for LTO support
if (${CMAKE_BUILD_TYPE} STREQUAL "Release")

    include(CheckIPOSupported)
    check_ipo_supported(RESULT LTO_SUPPORTED)
        
    if(LTO_SUPPORTED)
	set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
	endif()
endif()

# TODO: fix
message(DEBUG "looking for python environment in ${PYTHON_LOCATION_HINT}")
#import_python(HINT ${PYTHON_LOCATION_HINT})

# build flags
if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -DDEBUG -g")
    
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Profiling")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg -O3 -DNDEBUG")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg -O3 -DNDEBUG")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg -O3 -DNDEBUG")

elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -DNDEBUG")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftemplate-backtrace-limit=50")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
