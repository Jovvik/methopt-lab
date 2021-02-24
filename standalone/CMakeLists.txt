cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(LabStandalone LANGUAGES CXX)

# --- Import tools ----

include(../cmake/tools.cmake)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

CPMAddPackage("gh:jarro2783/cxxopts@2.2.0")

CPMAddPackage(NAME Lab SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)

# ---- Create standalone executable ----

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

add_executable(LabStandalone ${sources})

set_target_properties(LabStandalone PROPERTIES CXX_STANDARD 17 OUTPUT_NAME "Lab")

target_link_libraries(LabStandalone Lab::Lab cxxopts)
