cmake_minimum_required(VERSION 3.20)
project(MathTracker VERSION 1.0 LANGUAGES C CXX)

# ====== Set C++ Standard ======
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set default build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build." FORCE)
endif()

# Set configuration types
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Available configurations" FORCE)

# ====== Add Subdirectories ======
add_subdirectory(src)

# ====== Organize Sources in IDE ======
# source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${SRC_FILES})

#
# include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include(FetchContent)
FetchContent_Declare(
    Slint
    GIT_REPOSITORY https://github.com/slint-ui/slint.git

    # `release/1` will auto-upgrade to the latest Slint >= 1.0.0 and < 2.0.0
    # `release/1.0` will auto-upgrade to the latest Slint >= 1.0.0 and < 1.1.0
    GIT_TAG release/1
    SOURCE_SUBDIR api/cpp
)
FetchContent_MakeAvailable(Slint)

# ====== Build the Executable ======
add_executable(${CMAKE_PROJECT_NAME} main.cpp)

# ====== Link the library ======
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE PROGRESS_SRC)
