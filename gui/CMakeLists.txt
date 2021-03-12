cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(LabGui LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# --- Import tools ----

include(../cmake/tools.cmake)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

CPMAddPackage(NAME Lab SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)

find_package(
  Qt5
  COMPONENTS Widgets PrintSupport
  REQUIRED
)

file(GLOB headers CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
add_executable(LabGui ${headers} ${sources})
target_include_directories(LabGui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(LabGui PUBLIC Qt5::Widgets)
target_link_libraries(LabGui PUBLIC Qt5::PrintSupport)
target_link_libraries(LabGui PUBLIC Lab::Lab)
set_target_properties(LabGui PROPERTIES CXX_STANDARD 20)
set_source_files_properties(
  ${CMAKE_CURRENT_SOURCE_DIR}/source/qcustomplot.cpp
  PROPERTIES
  COMPILE_FLAGS "-w"
)
