cmake_minimum_required(VERSION 2.8)

PROJECT(libA)

set(libA_VTK_DIR "" CACHE PATH
  "VTK version for libA to link against")
if(NOT libA_VTK_DIR)
  message(FATAL_ERROR "Please set the VTK directory for libA")
endif()
find_package(VTK REQUIRED QUIET PATHS ${libA_VTK_DIR} NO_DEFAULT_PATH)
include(${VTK_USE_FILE})

option(BUILD_SHARED_LIBS "Build shared library" ON)

add_library(${PROJECT_NAME} classA.cxx)

if(VTK_LIBRARIES)
  target_link_libraries(${PROJECT_NAME} ${VTK_LIBRARIES})
else()
  target_link_libraries(${PROJECT_NAME} vtkHybrid vtkWidgets)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
  PUBLIC_HEADER "classA.h")

find_package(libB REQUIRED)
include_directories(
  ${libB_INCLUDE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR})

add_executable(${PROJECT_NAME}Exe classAExe.cxx)
target_link_libraries(${PROJECT_NAME}Exe
  ${PROJECT_NAME}
  ${libB_LIBRARIES})

foreach(P INCLUDE LIB BIN CMAKE)
  set(var ${P}_INSTALL_DIR)
  STRING(TOLOWER ${P} p)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(${var} "${CMAKE_INSTALL_PREFIX}/${p}")
  endif()
endforeach()

install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}Exe
  EXPORT ${PROJECT_NAME}Targets
  RUNTIME DESTINATION "${BIN_INSTALL_DIR}" COMPONENT bin
  LIBRARY DESTINATION "${LIB_INSTALL_DIR}" COMPONENT shlib
  PUBLIC_HEADER DESTINATION "${INCLUDE_INSTALL_DIR}" COMPONENT dev
  )

#export(TARGETS ${PROJECT_NAME}
#  FILE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}Targets.cmake)
#export(PACKAGE ${PROJECT_NAME})
#
#include(CMakePackageConfigHelpers)
#configure_package_config_file(${PROJECT_NAME}Config.cmake.in
#  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
#  INSTALL_DESTINATION ${CMAKE_INSTALL_DIR}
#  PATH_VARS INCLUDE_INSTALL_DIR LIB_INSTALL_DIR)
#write_basic_package_version_file(
#  ${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
#  VERSION 1.0.0
#  COMPATIBILITY SameMajorVersion)
#install(FILES
#  ${CMAKE_BINARY_DIR}/${PROJECT_NAME}Config.cmake
#  ${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
#  DESTINATION ${CMAKE_INSTALL_DIR})
