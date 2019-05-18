cmake_minimum_required(VERSION 3.13)
project(game-engine)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS window graphics REQUIRED)

add_executable(game-engine src/main.cpp src/Game.cpp src/Game.h src/Shader.cpp src/Shader.h src/Texture2D.cpp src/Texture2D.h src/ResourceManager.cpp src/ResourceManager.h src/SpriteRenderer.cpp src/SpriteRenderer.h src/GameObject.cpp src/GameObject.h src/GameLevel.cpp src/GameLevel.h)
target_link_libraries(game-engine sfml-window sfml-graphics GL GLEW SOIL)
