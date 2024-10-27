cmake_minimum_required(VERSION 3.10)
project(pong)

file(GLOB SOURCE_FILES
     core/*.hpp core/*.cpp
     game/*.hpp game/*.cpp
     render/*.hpp render/*.cpp
)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)
find_package(SDL2_ttf REQUIRED CONFIG REQUIRED COMPONENTS SDL2_ttf)

set(ASSETS_PATH "${CMAKE_BINARY_DIR}/assets/")
configure_file(config.h.in "${CMAKE_CURRENT_LIST_DIR}/config.h")

add_executable(${PROJECT_NAME}
    main.h
    main.cpp
    ${SOURCE_FILES}
)


if(TARGET SDL2::SDL2main)
	target_link_libraries(pong PRIVATE SDL2::SDL2main)
endif()
target_link_libraries(pong PRIVATE SDL2::SDL2)
target_link_libraries(pong PRIVATE SDL2_ttf::SDL2_ttf)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
