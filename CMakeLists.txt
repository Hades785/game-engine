cmake_minimum_required(VERSION 3.13)
project(game-engine)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS window graphics REQUIRED)

add_executable(game-engine src/main.cpp src/Game.cpp src/Game.h src/GameEngine/Assets/Shaders/Shader.cpp src/GameEngine/Assets/Shaders/Shader.h src/GameEngine/Assets/Sprites/Texture2D.cpp src/GameEngine/Assets/Sprites/Texture2D.h src/GameEngine/Assets/ResourceManager.cpp src/GameEngine/Assets/ResourceManager.h src/GameEngine/Assets/Sprites/SpriteRenderer.cpp src/GameEngine/Assets/Sprites/SpriteRenderer.h src/GameEngine/Assets/Levels/TileSet.cpp src/GameEngine/Assets/Levels/TileSet.h src/GameEngine/Assets/Sprites/Sprite.cpp src/GameEngine/Assets/Sprites/Sprite.h src/GameEngine/Util/Vertex.cpp src/GameEngine/Util/Vertex.h)
target_link_libraries(game-engine sfml-window sfml-graphics GL GLEW SOIL)
