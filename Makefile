# Makefile para Mutant Facility Game
# Estrutura: include/ para .hpp, src/ para .cpp

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
INCLUDES = -Iinclude
LDFLAGS = -lraylib -lm -lpthread -ldl

# Detectar sistema operacional
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    LDFLAGS += -lGL -lX11
endif
ifeq ($(UNAME_S),Darwin)
    LDFLAGS += -framework OpenGL -framework Cocoa -framework IOKit
endif

# Diretórios
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
BIN_DIR = bin

# Arquivos fonte
SOURCES = $(SRC_DIR)/main.cpp \
          $(SRC_DIR)/Game.cpp \
          $(SRC_DIR)/GameState.cpp \
          $(SRC_DIR)/Entities/Planta.cpp \
          $(SRC_DIR)/Entities/Drosera.cpp \
          $(SRC_DIR)/Entities/Dionaea.cpp \
          $(SRC_DIR)/Entities/Nicotiana.cpp \
          $(SRC_DIR)/Entities/FRND19.cpp \
          $(SRC_DIR)/Entities/Papoula.cpp \
          $(SRC_DIR)/Entities/Experimento.cpp \
          $(SRC_DIR)/Entities/Paciente.cpp \
          $(SRC_DIR)/Systems/SuperiorSystem.cpp \
          $(SRC_DIR)/Systems/MapSystem.cpp \
          $(SRC_DIR)/Systems/DNASystem.cpp \
          $(SRC_DIR)/Systems/ContainmentSystem.cpp \
          $(SRC_DIR)/Systems/InventorySystem.cpp \
          $(SRC_DIR)/Systems/RecipeSystem.cpp \
          $(SRC_DIR)/Systems/TimeSystem.cpp \
          $(SRC_DIR)/UI/PlantMenu.cpp \
          $(SRC_DIR)/UI/HackingMinigame.cpp \
          $(SRC_DIR)/UI/Button.cpp \
          $(SRC_DIR)/UI/HUD.cpp \
          $(SRC_DIR)/UI/Menu.cpp \
          $(SRC_DIR)/UI/UIManager.cpp \
          $(SRC_DIR)/Utils/SaveSystem.cpp \
          $(SRC_DIR)/Utils/FileManager.cpp \
          $(SRC_DIR)/Utils/Statistics.cpp

OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))
TARGET = $(BIN_DIR)/MutantFacility

# Regra padrão
all: directories $(TARGET)

# Criar diretórios
directories:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/Entities
	@mkdir -p $(BUILD_DIR)/Systems
	@mkdir -p $(BUILD_DIR)/UI
	@mkdir -p $(BIN_DIR)
	@mkdir -p saves

# Compilar executável
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo "✓ Compilação completa! Executável: $(TARGET)"

# Compilar objetos
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@
	@echo "✓ Compilado: $<"

# Limpar
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
	@echo "✓ Arquivos de build removidos"

# Executar
run: all
	./$(TARGET)

# Reinstalar (limpar e compilar)
rebuild: clean all

# Ajuda
help:
	@echo "Comandos disponíveis:"
	@echo "  make          - Compila o projeto"
	@echo "  make run      - Compila e executa"
	@echo "  make clean    - Remove arquivos de build"
	@echo "  make rebuild  - Limpa e recompila"
	@echo "  make help     - Mostra esta mensagem"

.PHONY: all clean run rebuild help directories