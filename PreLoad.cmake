cmake_minimum_required(VERSION 3.12)

# default compiler profile
if(NOT DEFINED CMAKE_PROFILE)
    set(CMAKE_PROFILE gcc84)
endif()

string(TOUPPER ${CMAKE_PROFILE} CMAKE_PROFILE_UC)

# default python location
if(DEFINED PYTHON)
    set(PYTHON_LOCATION_HINT "${PYTHON}" CACHE INTERNAL "" FORCE)
else()
    # default location
    set(PYTHON_LOCATION_HINT "/opt/miniconda/envs/py38" CACHE INTERNAL "" FORCE)
endif()

message(STATUS "info: defaulting python path to ${PYTHON_LOCATION_HINT} --")

if (CMAKE_PROFILE_UC STREQUAL "GCC93")

    set(DEVTOOLS_ROOT "/opt/gcc93")

    set(CXX_DIALECT          "17"						    CACHE INTERNAL "" FORCE)
    set(CMAKE_C_COMPILER     "${DEVTOOLS_ROOT}/bin/gcc"	    CACHE INTERNAL "" FORCE)
    set(CMAKE_CXX_COMPILER   "${DEVTOOLS_ROOT}/bin/g++"	    CACHE INTERNAL "" FORCE)
    set(LINKER_EXTRA_FLAG    "-fuse-ld=gold"                CACHE INTERNAL "" FORCE)
    set(R_LOCATION_HINT      "/opt/r40-gcc93"               CACHE INTERNAL "" FORCE)

    set(CONAN_BIN_PATH      "/opt/miniconda/envs/py38/bin"  CACHE INTERNAL "" FORCE)

    set(CONAN_FLAGS ${CONAN_FLAGS} "compiler.version=9.3"       )
    set(CONAN_FLAGS ${CONAN_FLAGS} "cppstd=${CXX_DIALECT}"      )
    set(CONAN_FLAGS ${CONAN_FLAGS} "compiler.libcxx=libstdc++11")

    set(CONAN_EXTRA_SETTINGS ${CONAN_FLAGS}                 CACHE INTERNAL "" FORCE)
    set(CMAKE_GENERATOR	     "Ninja"                        CACHE INTERNAL "" FORCE)
    set(CMAKE_MAKE_PROGRAM	 "${DEVTOOLS_ROOT}/bin/ninja" 	CACHE INTERNAL "" FORCE)
    set(CONAN_PROFILE        "gcc93"		                CACHE INTERNAL "" FORCE)

elseif(CMAKE_PROFILE_UC STREQUAL "GCC84")

    set(DEVTOOLS_ROOT "/opt/gcc84")

    set(CXX_DIALECT          "17"						    CACHE INTERNAL "" FORCE)
    set(CMAKE_C_COMPILER     "${DEVTOOLS_ROOT}/bin/gcc"	    CACHE INTERNAL "" FORCE)
    set(CMAKE_CXX_COMPILER   "${DEVTOOLS_ROOT}/bin/g++"	    CACHE INTERNAL "" FORCE)
    set(LINKER_EXTRA_FLAG    "-fuse-ld=gold"                CACHE INTERNAL "" FORCE)
    set(R_LOCATION_HINT      "/opt/r40-gcc84"               CACHE INTERNAL "" FORCE)

    set(CONAN_BIN_PATH      "/opt/miniconda/envs/py38/bin"  CACHE INTERNAL "" FORCE)

    set(CONAN_FLAGS ${CONAN_FLAGS} "compiler.version=8.4"       )
    set(CONAN_FLAGS ${CONAN_FLAGS} "cppstd=${CXX_DIALECT}"      )
    set(CONAN_FLAGS ${CONAN_FLAGS} "compiler.libcxx=libstdc++11")

    set(CONAN_EXTRA_SETTINGS ${CONAN_FLAGS}                 CACHE INTERNAL "" FORCE)
    set(CMAKE_GENERATOR	     "Ninja"                        CACHE INTERNAL "" FORCE)
    set(CMAKE_MAKE_PROGRAM	 "${DEVTOOLS_ROOT}/bin/ninja" 	CACHE INTERNAL "" FORCE)
    set(CONAN_PROFILE        "gcc84"		                CACHE INTERNAL "" FORCE)

else()
    message(FATAL_ERROR "Error: ${CMAKE_PROFILE} - Unknown configuration passed. Aborting ... ")
endif()

if(CMAKE_BUILD_TYPE)
    string(TOUPPER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_UC)
else()
    set(CMAKE_BUILD_TYPE_UC "RELEASE")
endif()

if(CMAKE_BUILD_TYPE_UC STREQUAL "RELEASE")
    message(STATUS "info: cmake build type set to \"Release\" --")
    set(CMAKE_BUILD_TYPE "Release" CACHE INTERNAL "" FORCE)
elseif(CMAKE_BUILD_TYPE_UC STREQUAL "DEBUG")
    message(STATUS "info: cmake build type set to \"Debug\" --")
    set(CMAKE_BUILD_TYPE "Debug" CACHE INTERNAL "" FORCE)
elseif(CMAKE_BUILD_TYPE_UC STREQUAL "PROFILING")
    message(STATUS "info: cmake build type set to \"Profiling\" --")
    set(CMAKE_BUILD_TYPE "Profiling" CACHE INTERNAL "" FORCE)
else()
    message(FATAL_ERROR "Error: ${CMAKE_BUILD_TYPE} - Unknown build type passed. Aborting...")
endif()

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}" CACHE PATH "Cmake prefix" FORCE)
message(STATUS "installation directory set to ${CMAKE_INSTALL_PREFIX}")

set(CONAN_USER    "jvermosen"	CACHE STRING "thirdparty libs conan user"		FORCE)
set(CONAN_CHANNEL "stable"		CACHE STRING "thirdparty libs conan channel"	FORCE)
