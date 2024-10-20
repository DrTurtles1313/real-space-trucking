cmake_minimum_required(VERSION 3.29)
# Definitions
set(PROJECT_NAME real_space_trucking_raylib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

project(${PROJECT_NAME})
set(CMAKE_C_STANDARD 11)

# Include paths
set(INCLUDE_DIRS ${INCLUDE_DIRS})
# Assign the include directories
include_directories(${INCLUDE_DIRS})

set(SOURCE_FILES src/main.c)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

find_package(raylib 4.5.0 REQUIRED)
target_link_libraries(${PROJECT_NAME} raylib)