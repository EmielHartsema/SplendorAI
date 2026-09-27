set(BIN_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/bin
)

add_library(SplendorInterface INTERFACE)

target_include_directories(SplendorInterface
    INTERFACE
        "${CMAKE_CURRENT_SOURCE_DIR}/inc"
)

target_compile_features(SplendorInterface
    INTERFACE
        cxx_std_20
)

# Temporary home for the example decision makers.
# This can move to a separate agent project later.
add_library(SplendorDecisionMakers
    src/DecisionMaker.cpp
)

target_link_libraries(SplendorDecisionMakers
    PUBLIC
        SplendorInterface
)

set_target_properties(SplendorDecisionMakers PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}/Debug"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}/Release"
)