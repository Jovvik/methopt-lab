cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(LabGui LANGUAGES CXX)

# --- Import tools ----

include(../cmake/tools.cmake)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

CPMAddPackage(NAME Lab SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)

find_package(
  Qt5
  COMPONENTS Widgets
  REQUIRED
)

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
add_executable(LabGui ${sources})

file(GLOB assets ${CMAKE_CURRENT_SOURCE_DIR}/assets/*)
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

target_link_libraries(LabGui Qt5::Widgets)
target_link_libraries(LabGui Lab::Lab)
set_target_properties(LabGui PROPERTIES CXX_STANDARD 20)
