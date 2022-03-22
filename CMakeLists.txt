cmake_minimum_required(VERSION 3.2)

PROJECT(dmredispp)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(cmake/ModuleImport.cmake)
INCLUDE(cmake/ModuleCompileOptions.cmake)
ModuleSetCompileOptions()
ModuleSetWinCompilerFlags()

SET(DMREDISPP_VERSION_MAJOR "1")
SET(DMREDISPP_VERSION_MINOR "0")
SET(DMREDISPP_VERSION_PATCH "1")
SET(DMREDISPP_VERSION "${DMREDISPP_VERSION_MAJOR}.${DMREDISPP_VERSION_MINOR}.${DMREDISPP_VERSION_PATCH}")

MESSAGE(STATUS "VERSION: ${DMREDISPP_VERSION}")

OPTION(USE_DMREDISPP "use dmredispp" OFF)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/include/dmredispp_config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/include/dmredispp_config.h)

ModuleImportAll("thirdparty")
LibImport("dmredispp_module" "src/dmredispp_module")
ExeImport("test" "dmevent;tacopie;cpp_redis")

#ADD_CUSTOM_COMMAND(
#TARGET dmredispptest
#PRE_BUILD
#COMMAND ${CMAKE_COMMAND} -E copy_if_different
#${CMAKE_CURRENT_SOURCE_DIR}/config/test.csv
#$<TARGET_FILE_DIR:dmredispptest>
#)

#INSTALL(DIRECTORY include/ DESTINATION include)
#INSTALL(TARGETS dmredispp
#        RUNTIME DESTINATION bin
#        LIBRARY DESTINATION lib
#        ARCHIVE DESTINATION lib)

#SET(DMREDISPP_LIBS "dmredispp")
#MARK_AS_ADVANCED(${DMREDISPP_LIBS})
