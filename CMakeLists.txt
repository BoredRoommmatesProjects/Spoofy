cmake_minimum_required(VERSION 3.0.0)
project(firstSFMLProject VERSION 0.1.0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(SFML COMPONENTS graphics audio REQUIRED)

add_executable(firstSFMLProject src/firstSFMLProject/main.cpp)
target_link_libraries(firstSFMLProject sfml-graphics sfml-audio)
