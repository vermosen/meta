cmake_minimum_required (VERSION 3.13)

option(SKIP_CONAN_PACKAGE "skip conan package generation" OFF)
option(BUILD_TEST         "build test suite" 			   ON)

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

set(${PROJECT_NAME_U}_MAJOR_VERSION 0)
set(${PROJECT_NAME_U}_MINOR_VERSION 1)
set(${PROJECT_NAME_U}_BUILD_VERSION 8)

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

set(GTEST_VERS     "1.8.1" )

set(PACKAGES
   gtest
)

message(STATUS "package list has been set to ${PACKAGES}")

# imported packages
load_packages(
	NAME ${PACKAGES}
	PROFILE ${CONAN_PROFILE}
	SETTINGS ${CONAN_EXTRA_SETTINGS}
	UPDATE
)

message(DEBUG "CONAN_LIBS set to ${CONAN_LIBS}")

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