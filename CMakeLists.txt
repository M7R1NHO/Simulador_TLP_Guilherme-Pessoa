cmake_minimum_required(VERSION 3.20)
project(MutantFacility)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Encontrar Raylib
# Raylib (pré-compilada)
set(RAYLIB_PATH "C:/raylib-5.0_win64_mingw-w64")
include_directories(${RAYLIB_PATH}/include)
link_directories(${RAYLIB_PATH}/lib)

# Diretórios de include
include_directories(${CMAKE_SOURCE_DIR}/include)

# Arquivos fonte
set(SOURCES
    src/main.cpp
    src/Game.cpp
    src/GameState.cpp
    src/Entities/Planta.cpp
    src/Entities/Drosera.cpp
    src/Entities/Dionaea.cpp
    src/Entities/Nicotiana.cpp
    src/Entities/FRND19.cpp
    src/Entities/Papoula.cpp
    src/Entities/Experimento.cpp
    src/Entities/Paciente.cpp
    src/Systems/SuperiorSystem.cpp
    src/Systems/MapSystem.cpp
    src/Systems/DNASystem.cpp
    src/Systems/ContainmentSystem.cpp
    src/Systems/InventorySystem.cpp
    src/Systems/RecipeSystem.cpp
    src/Systems/TimeSystem.cpp
    src/UI/PlantMenu.cpp
    src/UI/HackingMinigame.cpp
    src/UI/Button.cpp
    src/UI/HUD.cpp
    src/UI/Menu.cpp
    src/UI/UIManager.cpp
    src/Utils/SaveSystem.cpp
    src/Utils/FileManager.cpp
    src/Utils/Statistics.cpp
)

# Criar executável
add_executable(${PROJECT_NAME} ${SOURCES})

# Linkar Raylib (por plataforma)
if (WIN32)
    target_link_libraries(${PROJECT_NAME} raylib winmm gdi32 opengl32)
elseif(APPLE)
    target_link_libraries(${PROJECT_NAME} raylib "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
else()
    target_link_libraries(${PROJECT_NAME} raylib m pthread dl rt X11)
endif()

# Copiar recursos para o diretório de build
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

# Instalação
install(TARGETS ${PROJECT_NAME} DESTINATION bin)