cmake_minimum_required (VERSION 3.13)

# note: this script is left in a separate file *on purpose*
# see https://cmake.org/cmake/help/v3.7/command/install.html

#####################################
#     generate the conan export     #
#####################################

export_project(
	NAME ${PROJECT_NAME}
	NAMESPACE ${PROJECT_NAME}
	REVISION ${${PROJECT_NAME_U}_VERSION}
	DIRECTORY cmake/package # for later use
)

if (SKIP_CONAN_PACKAGE STREQUAL "OFF")

	conan_export(
		PACKAGE ${PROJECT_NAME}
		REVISION ${${PROJECT_NAME_U}_VERSION}
		USER ${CONAN_USER}
		CHANNEL ${CONAN_CHANNEL}
		PROFILE ${CONAN_PROFILE}
		DIRECTORY conan
	)

endif()