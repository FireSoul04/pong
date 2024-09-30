cmake_minimum_required(VERSION 3.10)
project(pong)

file(GLOB SOURCE_FILES
     core/*.hpp core/*.cpp
     game/*.hpp game/*.cpp
     render/*.hpp render/*.cpp
)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

set(ASSETS_PATH "${CMAKE_BINARY_DIR}/assets/")
configure_file(config.h.in "${CMAKE_CURRENT_LIST_DIR}/config.h")

add_executable(${PROJECT_NAME}
    main.h
    main.cpp
    ${SOURCE_FILES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::Main)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::TTF)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
