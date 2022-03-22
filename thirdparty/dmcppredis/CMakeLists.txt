cmake_minimum_required(VERSION 3.2)

PROJECT(dmcppredis)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(cmake/ModuleImport.cmake)
INCLUDE(cmake/ModuleCompileOptions.cmake)
ModuleSetCompileOptions()

ADD_DEFINITIONS(-DUSE_DMCPPREDIS)

ModuleImport("tacopie" "thirdparty/tacopie")

LibImportDepends("cpp_redis" "src" "tacopie")

ExeImport("examples" "tacopie;cpp_redis")
