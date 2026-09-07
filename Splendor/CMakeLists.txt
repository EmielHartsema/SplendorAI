# ==========================================
# Splendor
# ==========================================

# ------------------------------------------
# Build output
# ------------------------------------------

set(SPLENDOR_BIN_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/bin
)

# ------------------------------------------
# Production library
# ------------------------------------------

add_library(SplendorLib
    src/Game.cpp
)

target_include_directories(SplendorLib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

target_compile_features(SplendorLib
    PUBLIC
        cxx_std_20
)

set_target_properties(SplendorLib PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${SPLENDOR_BIN_DIR}/Debug"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${SPLENDOR_BIN_DIR}/Release"
)

# ------------------------------------------
# Splendor executable
# ------------------------------------------

add_executable(Splendor
    src/main.cpp
)

target_link_libraries(Splendor
    PRIVATE
        SplendorLib
)

set_target_properties(Splendor PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${SPLENDOR_BIN_DIR}/Debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${SPLENDOR_BIN_DIR}/Release"
)

# ------------------------------------------
# Unit tests
# ------------------------------------------

add_executable(SplendorTests
    tst/GameTest.cpp
)

target_link_libraries(SplendorTests
    PRIVATE
        SplendorLib
        GTest::gtest_main
)

set_target_properties(SplendorTests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${SPLENDOR_BIN_DIR}/Debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${SPLENDOR_BIN_DIR}/Release"
)


include(GoogleTest)

gtest_discover_tests(SplendorTests)