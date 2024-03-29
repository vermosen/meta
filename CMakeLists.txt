cmake_minimum_required (VERSION 3.13)

option(SKIP_CONAN_PACKAGE "skip conan package generation" OFF)
option(BUILD_TEST         "build test suite" 			         ON)
option(LLVM_TOOLING      "enable include-what-you-use"    OFF)

set(PROJECT_HOME "${CMAKE_CURRENT_LIST_DIR}")
set(PROJECT_NAME meta CACHE STRING "" FORCE)
set(PROJECT_NAMESPACE meta CACHE STRING "" FORCE)
string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_U)

message(STATUS "*** variable PROJECT_NAME set to: ${PROJECT_NAME} ***")
message(STATUS "*** variable PROJECT_NAMESPACE set to: ${PROJECT_NAMESPACE} ***")
message(STATUS "*** variable PROJECT_HOME set to: ${PROJECT_HOME} ***")

message(STATUS "*** retrieving cmake configuration from ${PROJECT_HOME}/cmake ***")

##############################
#      include toolsets      #
##############################

include("${PROJECT_HOME}/cmake/CMakeLists.txt")

###########################
#  defines cmake project  #
###########################

set(${PROJECT_NAME_U}_MAJOR_VERSION  0)
set(${PROJECT_NAME_U}_MINOR_VERSION  1)
set(${PROJECT_NAME_U}_BUILD_VERSION 13)

set(${PROJECT_NAME_U}_VERSION
  ${${PROJECT_NAME_U}_MAJOR_VERSION}.${${PROJECT_NAME_U}_MINOR_VERSION}.${${PROJECT_NAME_U}_BUILD_VERSION})

message(STATUS "project version set to ${${PROJECT_NAME_U}_VERSION}")

PROJECT(
	${PROJECT_NAME}
	LANGUAGES C CXX
	VERSION	${${PROJECT_NAME_U}_VERSION}
	DESCRIPTION "the meta library"
)

##############################
# import thirdparty packages #
##############################

set(GTEST_VERS  "1.8.1" )
set(BOOST_VERS "1.76.0" )
set(IWYU_VERS  "0.15.0" )

set(PACKAGES
   gtest
	 boost
)

if (LLVM_TOOLING)
	set(PACKAGES ${PACKAGES} iwyu)
endif()

message(STATUS "package list has been set to ${PACKAGES}")

load_packages(
	NAME ${PACKAGES}
	USER ${CONAN_USERNAME}
	CHANNEL ${CONAN_CHANNEL}
	PROFILE ${CONAN_PROFILE}
	SETTINGS "build_type=${CMAKE_BUILD_TYPE}"
	OPTIONS ""
	UPDATE
)

if (LLVM_TOOLING)

	# TODO: setup_iwyu(PATH ${CONAN_BIN_DIRS_IWYU} OPTIONS any)

	# add iwyu support
	message(DEBUG "looking for iwyu in folder ${CONAN_BIN_DIRS_IWYU}")

	find_program(iwyu NAMES include-what-you-use HINTS ${CONAN_BIN_DIRS_IWYU} REQUIRED)

	if(NOT iwyu)
		message(WARNING "cannot find iwyu in path ${CONAN_BIN_DIRS_IWYU}")
	else()
		message(STATUS "iwyu found in path ${CONAN_BIN_DIRS_IWYU}")
	endif()

	list(APPEND iwyu -Xiwyu;any)

	# for some reason, we need to add up this -> set in the conan package
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/opt/clang11/lib/clang/11.0.0/include")

endif()

#####################################
#          add the sources          #
#####################################

include_directories(src)

#####################################
#     add the project libraries     #
#####################################

add_subdirectory(src/meta)

#####################################
#             ctest setup           #
#####################################

include(CTest)
add_subdirectory(tests)

#####################################
#     generate the conan export     #
#####################################

add_subdirectory(conan)