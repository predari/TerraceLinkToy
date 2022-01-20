cmake_minimum_required (VERSION 3.11.4)


project (HELLO)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake.modules/")

include_directories(${CMAKE_SOURCE_DIR})

# OpenMP
find_package(OpenMP)

add_executable(HELLO hello.cpp)

if (NOT TERRACE_COMPILE_DIR)
  message(FATAL_ERROR "Please specify TERRACE_COMPILE_DIR")
endif()
target_include_directories(HELLO BEFORE PUBLIC "${TERRACE_COMPILE_DIR}/include")
target_compile_options(HELLO PRIVATE -m64)
target_compile_definitions(HELLO PRIVATE OPENMP=1)

find_library(TERRACE libterrace.so PATH ${TERRACE_COMPILE_DIR})
target_link_libraries(HELLO PRIVATE ${TERRACE})
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath -Wl,${TERRACE_COMPILE_DIR}")


target_link_libraries(HELLO PRIVATE OpenMP::OpenMP_CXX stdc++fs)

install(TARGETS HELLO DESTINATION bin)

