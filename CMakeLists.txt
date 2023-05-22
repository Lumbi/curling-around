cmake_minimum_required(VERSION 3.25)

set(CMAKE_VERBOSE_MAKEFILE ON)

project(CurlingAround)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)

if(MSVC)
    add_compile_options(/permissive- /W4 /W4 /w14640)
elseif(APPLE)
    add_compile_options(-fsanitize=address)
    add_link_options(-fsanitize=address)
    add_compile_options(-Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wpedantic -Wunused -Woverloaded-virtual)
endif()

if(MSVC)
    set(CMAKE_FIND_LIBRARY_PREFIXES "")
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib" ".dll")
elseif(APPLE)
    set(CMAKE_FIND_LIBRARY_PREFIXES "" "lib")
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a" ".dylib")
endif()

find_package(OpenGL REQUIRED)

if(MSVC)
    find_library(SDL2_LIBRARIES NAMES SDL2 PATHS ${CMAKE_SOURCE_DIR}/lib/SDL2/bin)
    find_library(ASSIMP_LIBRARIES NAMES assimp PATHS ${CMAKE_SOURCE_DIR}/lib/assimp/bin)
    find_library(GLEW_LIBRARIES NAMES glew glew32 PATHS ${CMAKE_SOURCE_DIR}/lib/glew/bin)
elseif(APPLE)
    find_package(SDL2 REQUIRED)
    find_library(ASSIMP_LIBRARIES NAMES assimp PATHS ${CMAKE_SOURCE_DIR}/lib/assimp/bin)
    find_library(GLEW_LIBRARIES NAMES glew glew32 PATHS ${CMAKE_SOURCE_DIR}/lib/glew/bin)
endif()

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
    src/rendering/Renderer.cpp
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
    src/game/Parameter.cpp
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

add_library(SDL2 SHARED IMPORTED)
add_library(assimp SHARED IMPORTED)
add_library(glew SHARED IMPORTED)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} PRIVATE lib)

target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib/SDL2/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib/assimp/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib/glew/include)

target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${ASSIMP_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${GLEW_LIBRARIES})

file(COPY asset DESTINATION ${CMAKE_BINARY_DIR})
