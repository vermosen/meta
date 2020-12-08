cmake_minimum_required (VERSION 3.13)

# note: this script is left in a separate file *on purpose*
# ref: https://stackoverflow.com/questions/43875499/do-post-processing-after-make-install-in-cmake

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