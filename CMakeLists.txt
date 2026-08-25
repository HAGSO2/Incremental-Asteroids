#----------------------------------------
# Cmake 
#----------------------------------------
cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+

#----------------------------------------
# Project name and version
#----------------------------------------
project(FirstC++RayTest VERSION 1.0 LANGUAGES C CXX)

#----------------------------------------
#Compile options
#----------------------------------------
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


#----------------------------------------
# Dependencies
#----------------------------------------
set(RAYLIB_VERSION 6.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if(NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  fetchcontent_declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  fetchcontent_getproperties(raylib)
  if(NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    fetchcontent_makeavailable(raylib)
  endif()
endif()

#----------------------------------------
# Project targets
#----------------------------------------

#For simple projects:
#add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(engine)
add_subdirectory(game)
set(raylib_VERBOSE 1)
#target_link_libraries(${PROJECT_NAME} raylib)