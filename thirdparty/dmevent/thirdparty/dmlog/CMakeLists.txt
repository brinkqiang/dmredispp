cmake_minimum_required(VERSION 3.2)

PROJECT(dmlog)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(cmake/ModuleImport.cmake)
INCLUDE(cmake/ModuleCompileOptions.cmake)
ModuleSetCompileOptions()

#SET(CMAKE_CXX_CPPCHECK "cppcheck")
#LIST(APPEND CMAKE_CXX_CPPCHECK "--enable=all")

SET(DMLOG_VERSION_MAJOR "1")
SET(DMLOG_VERSION_MINOR "0")
SET(DMLOG_VERSION_PATCH "1")
SET(DMLOG_VERSION "${DMLOG_VERSION_MAJOR}.${DMLOG_VERSION_MINOR}.${DMLOG_VERSION_PATCH}")

MESSAGE(STATUS "VERSION: ${DMLOG_VERSION}")

ADD_DEFINITIONS(-DUSE_DMLOG)

ModuleImport("dmformat" "thirdparty/dmformat")
ExeImport("test" "")
