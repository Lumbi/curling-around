cmake_minimum_required(VERSION 3.25)

set(CMAKE_VERBOSE_MAKEFILE ON)

project(CurlingAround)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)
add_compile_options(-Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wpedantic -Wunused -Woverloaded-virtual)

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_library(ASSIMP_LIBRARIES NAMES assimp PATHS ${CMAKE_SOURCE_DIR}/lib/assimp/bin)

add_executable(
    ${PROJECT_NAME}
    src/Main.cpp
    src/Time.cpp
    src/math/Matrix.cpp
    src/math/Vector.cpp
    src/math/Transform.cpp
    src/rendering/Camera.cpp
    src/rendering/Vertex.cpp
    src/rendering/Shader.cpp
    src/rendering/Texture.cpp
    src/rendering/Material.cpp
    src/rendering/Mesh.cpp
    src/rendering/Model.cpp
    src/rendering/ModelRenderer.cpp
    src/input/Keyboard.cpp
    src/input/Input.cpp
    src/physics/Collider.cpp
    src/physics/PhysicsBody.cpp
    src/physics/Physics.cpp
    src/physics/Collisions.cpp
    src/asset/TextureLoader.cpp
    src/asset/ModelLoader.cpp
    src/asset/ShaderLibrary.cpp
    src/asset/AssetLibrary.cpp
    src/game/Component.cpp
    src/game/Actor.cpp
    src/game/Scene.cpp
    src/game/components/ModelComponent.cpp
    src/game/components/PhysicsBodyComponent.cpp
    src/game/actors/CurlingStone.cpp
    src/game/actors/Obstacle.cpp
    src/game/PlayerController.cpp
    src/game/FreeCameraController.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE src)

add_library(assimp SHARED IMPORTED)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} PRIVATE lib)

target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib/assimp/include)

target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${ASSIMP_LIBRARIES})

file(COPY asset DESTINATION ${CMAKE_BINARY_DIR})
