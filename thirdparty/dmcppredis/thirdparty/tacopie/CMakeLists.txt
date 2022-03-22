cmake_minimum_required(VERSION 3.2)

PROJECT(tacopie)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(cmake/ModuleImport.cmake)
INCLUDE(cmake/ModuleCompileOptions.cmake)
ModuleSetCompileOptions()

ADD_DEFINITIONS(-DUSE_TACOPIE)

LibImport("tacopie" "src")

ExeImport("examples" "tacopie")
