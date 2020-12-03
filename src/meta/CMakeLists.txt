cmake_minimum_required (VERSION 3.13)

SET(TARGET_NAME meta)

setup_component(TARGET ${TARGET_NAME})

file(GLOB_RECURSE TARGET_HEADERS CONFIGURE_DEPENDS "*.h")

add_library(${TARGET_NAME} INTERFACE)

target_include_directories(
    ${TARGET_NAME} INTERFACE
)

install_library(
    NAME ${TARGET_NAME} 
    HEADERS ${TARGET_HEADERS} 
    PACKAGE ${PROJECT_NAME}
)
