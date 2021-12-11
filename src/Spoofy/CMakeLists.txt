# Find source files
FILE(GLOB_RECURSE SPOOFY_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Build library
add_library(Spoofy STATIC
    ${SPOOFY_SOURCES}
)

target_link_libraries(Spoofy
    ${SPOOFY_PACKAGES_LIBRARIES}
    ${SPOOFY_DEPENDENCIES}
)