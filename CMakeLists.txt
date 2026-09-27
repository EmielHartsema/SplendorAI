cmake_minimum_required(VERSION 3.20)

project(
    SplendorAI
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# ==========================================
# Dependencies
# ==========================================

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)


# ==========================================
# Testing
# ==========================================

enable_testing()


# ==========================================
# Components
# ==========================================
add_subdirectory(SplendorInterface)
add_subdirectory(SplendorCore)


# ------------------------------------------
# Splendor executable
# ------------------------------------------
add_executable(Splendor
    main.cpp
)

target_link_libraries(Splendor
    PRIVATE
        SplendorLib
        SplendorDecisionMakers
)

set_target_properties(Splendor PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/bin/Debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/bin/Release"
)
    