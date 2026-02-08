#!/bin/bash

# Script de compilação para Mutant Facility Game
# Estrutura: include/ (.hpp) + src/ (.cpp)

set -e

PROJECT_NAME="MutantFacility"
BUILD_DIR="build"
BIN_DIR="bin"

GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m'

echo_info() {
    echo -e "${GREEN}[INFO]${NC} $1"
}

echo_warn() {
    echo -e "${YELLOW}[WARN]${NC} $1"
}

echo_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

check_dependencies() {
    echo_info "Verificando dependencias..."
    
    if ! pkg-config --exists raylib 2>/dev/null; then
        echo_warn "Raylib nao encontrado via pkg-config"
        echo_warn "Tentando compilar mesmo assim..."
    else
        RAYLIB_VERSION=$(pkg-config --modversion raylib)
        echo_info "Raylib ${RAYLIB_VERSION} encontrado!"
    fi
}

create_directories() {
    echo_info "Criando diretorios..."
    mkdir -p ${BUILD_DIR}
    mkdir -p ${BIN_DIR}
    mkdir -p saves
    mkdir -p assets/textures
    mkdir -p assets/fonts
    mkdir -p assets/sounds
}

clean() {
    echo_info "Limpando arquivos de build..."
    rm -rf ${BUILD_DIR}
    rm -rf ${BIN_DIR}
    echo_info "Limpeza concluida!"
}

build_cmake() {
    echo_info "Compilando com CMake..."
    
    create_directories
    cd ${BUILD_DIR}
    
    cmake ..
    make -j$(nproc)
    
    cd ..
    echo_info "Compilacao CMake concluida!"
}

build_make() {
    echo_info "Compilando com Make..."
    
    create_directories
    make -j$(nproc)
    
    echo_info "Compilacao Make concluida!"
}

build_manual() {
    echo_info "Compilando manualmente..."
    
    create_directories
    
    g++ -std=c++17 -O2 -Wall -Wextra \
        -Iinclude \
        src/main.cpp \
        src/Game.cpp \
        src/GameState.cpp \
        src/Entities/Planta.cpp \
        src/Entities/Drosera.cpp \
        src/Entities/Dionaea.cpp \
        src/Entities/Nicotiana.cpp \
        src/Entities/FRND19.cpp \
        src/Entities/Papoula.cpp \
        src/Entities/Experimento.cpp \
        src/Entities/Paciente.cpp \
        src/Systems/SuperiorSystem.cpp \
        src/Systems/MapSystem.cpp \
        src/Systems/DNASystem.cpp \
        src/Systems/ContainmentSystem.cpp \
        src/Systems/InventorySystem.cpp \
        src/Systems/RecipeSystem.cpp \
        src/Systems/TimeSystem.cpp \
        src/UI/PlantMenu.cpp \
        src/UI/HackingMinigame.cpp \
        src/UI/Button.cpp \
        src/UI/HUD.cpp \
        src/UI/Menu.cpp \
        src/UI/UIManager.cpp \
        src/Utils/SaveSystem.cpp \
        src/Utils/FileManager.cpp \
        src/Utils/Statistics.cpp \
        -lraylib -lm -lpthread -ldl \
        -o ${BIN_DIR}/${PROJECT_NAME}
    
    echo_info "Compilacao manual concluida!"
}

run_game() {
    if [ -f "${BIN_DIR}/${PROJECT_NAME}" ]; then
        echo_info "Executando ${PROJECT_NAME}..."
        ./${BIN_DIR}/${PROJECT_NAME}
    elif [ -f "${BUILD_DIR}/${PROJECT_NAME}" ]; then
        echo_info "Executando ${PROJECT_NAME}..."
        ./${BUILD_DIR}/${PROJECT_NAME}
    else
        echo_error "Executavel nao encontrado! Compile primeiro."
        exit 1
    fi
}

show_help() {
    echo "=========================================="
    echo "  Script de Build - Mutant Facility Game"
    echo "=========================================="
    echo ""
    echo "Uso: ./build.sh [opcao]"
    echo ""
    echo "Opcoes:"
    echo "  (vazio)  - Compilar com CMake"
    echo "  cmake    - Compilar com CMake"
    echo "  make     - Compilar com Make"
    echo "  manual   - Compilar manualmente com g++"
    echo "  clean    - Limpar arquivos de build"
    echo "  run      - Executar o jogo"
    echo "  rebuild  - Limpar e recompilar"
    echo "  help     - Mostrar esta mensagem"
    echo ""
}

main() {
    case "${1:-cmake}" in
        cmake)
            check_dependencies
            build_cmake
            echo_info "Para executar: ./build.sh run"
            ;;
        make)
            check_dependencies
            build_make
            echo_info "Para executar: ./build.sh run"
            ;;
        manual)
            check_dependencies
            build_manual
            echo_info "Para executar: ./build.sh run"
            ;;
        clean)
            clean
            ;;
        run)
            run_game
            ;;
        rebuild)
            clean
            check_dependencies
            build_cmake
            echo_info "Para executar: ./build.sh run"
            ;;
        help|--help|-h)
            show_help
            ;;
        *)
            echo_error "Opcao invalida: $1"
            echo_info "Use './build.sh help' para ver opcoes"
            exit 1
            ;;
    esac
}

main "$@"