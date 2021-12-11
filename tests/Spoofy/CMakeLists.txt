add_executable(SpoofyGame main.cpp)
target_link_libraries(SpoofyGame 
    PUBLIC Spoofy
    ${SPOOFY_DEPENDENCIES}
)