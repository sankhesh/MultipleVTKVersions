cmake_minimum_required(VERSION 2.8)

PROJECT(libB)

set(libB_VTK_DIR "" CACHE PATH
  "VTK version for libB to link against")
if(NOT libB_VTK_DIR)
  message(FATAL_ERROR "Please set the VTK directory for libB")
endif()
find_package(VTK REQUIRED QUIET PATHS ${libB_VTK_DIR} NO_DEFAULT_PATH)
include(${VTK_USE_FILE})

option(BUILD_SHARED_LIBS "Build shared library" ON)

add_library(${PROJECT_NAME} classB.cxx)

if(VTK_LIBRARIES)
  target_link_libraries(${PROJECT_NAME} ${VTK_LIBRARIES})
else()
  target_link_libraries(${PROJECT_NAME} vtkHybrid vtkWidgets)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
  PUBLIC_HEADER "classB.h")

foreach(P LIB BIN CMAKE)
  set(var ${P}_INSTALL_DIR)
  set(${var} "${CMAKE_CURRENT_BINARY_DIR}")
endforeach()
set(INCLUDE_INSTALL_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

include(CMakePackageConfigHelpers)
configure_package_config_file(${PROJECT_NAME}Config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_DIR}
  PATH_VARS INCLUDE_INSTALL_DIR LIB_INSTALL_DIR)

foreach(P INCLUDE LIB BIN CMAKE)
  set(var ${P}_INSTALL_DIR)
  string(TOLOWER ${P} p)
  set(${var} "${CMAKE_INSTALL_PREFIX}/${p}")
endforeach()

configure_package_config_file(${PROJECT_NAME}Config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/${PROJECT_NAME}Config.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_DIR}
  PATH_VARS INCLUDE_INSTALL_DIR LIB_INSTALL_DIR)

install(TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  RUNTIME DESTINATION "${BIN_INSTALL_DIR}" COMPONENT bin
  LIBRARY DESTINATION "${LIB_INSTALL_DIR}" COMPONENT shlib
  PUBLIC_HEADER DESTINATION "${INCLUDE_INSTALL_DIR}" COMPONENT dev
  )

export(TARGETS ${PROJECT_NAME}
  FILE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake)
export(PACKAGE ${PROJECT_NAME})
install(EXPORT ${PROJECT_NAME}Targets
  FILE ${PROJECT_NAME}Targets.cmake
  DESTINATION ${CMAKE_INSTALL_DIR}
  )

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
  VERSION 1.0.0
  COMPATIBILITY SameMajorVersion)
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/${PROJECT_NAME}Config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
  DESTINATION ${CMAKE_INSTALL_DIR})
