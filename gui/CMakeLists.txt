cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(LabGui LANGUAGES CXX)

CPMAddPackage(NAME Lab SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)

# --- Import tools ----

include(../cmake/tools.cmake)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

find_package(
  Qt5
  COMPONENTS Widgets
  REQUIRED
)

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*)
add_executable(LabGui ${sources})

target_link_libraries(LabGui Qt5::Widgets)
target_link_libraries(LabGui Lab::Lab)
set_target_properties(LabGui PROPERTIES CXX_STANDARD 20)
