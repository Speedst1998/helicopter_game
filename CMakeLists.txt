cmake_minimum_required(VERSION 3.0.0)
project(helicopter_game VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(helicopter_game_exec)
target_sources(helicopter_game_exec PUBLIC main.cpp 
                                        texture.cpp 
                                        shader.cpp 
                                        resource_manager.cpp 
                                        resource_manager.hpp 
                                        shader.hpp texture.hpp
                                        sprite_renderer.hpp 
                                        sprite_renderer.cpp
                                        game.hpp
                                        game.cpp
                                        game_object.hpp
                                        game_object.cpp
                                        game_level.hpp
                                        game_level.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_include_directories(helicopter_game_exec PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(helicopter_game_exec PUBLIC "include/helicopter_game")
target_include_directories(helicopter_game_exec PUBLIC "third_party/stb")
target_include_directories(helicopter_game_exec PUBLIC "third_party/glad")
target_link_directories(helicopter_game_exec PUBLIC "lib")
target_link_libraries(helicopter_game_exec PUBLIC glfw3 opengl32)
add_subdirectory(third_party)

add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders
        ${CMAKE_BINARY_DIR}/shaders
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/textures
        ${CMAKE_BINARY_DIR}/textures
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/levels
        ${CMAKE_BINARY_DIR}/levels
    COMMENT "Copying resources to build directory"
)

add_dependencies(helicopter_game_exec copy_resources)