#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>

// Configurações de janela
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int FPS = 60;

// Configurações de tempo
const int NIGHT_DURATION = 360; // 6 minutos em segundos
const int TOTAL_DAYS = 5;

// Estados do dia
enum class DayPhase {
    DUSK,    // Anoitecer
    NIGHT    // Noite
};

// Estados do jogo
enum class GamePhase {
    MENU,
    SELECTING_PATIENT,
    NIGHT_PHASE,
    DAY_COMPLETE,
    GAME_OVER,
    CREDITS
};

// Tipos de plantas
enum class PlantType {
    DROSERA,
    DIONAEA,
    NICOTIANA,
    FRND19,
    PAPOULA,
    EMPTY
};

// Estados de mutação
enum class MutationState {
    NORMAL,
    FERTILIZED,      // Adubada
    MUTANT,
    MUTANT_FERTILIZED // Mutante Adubada
};

// Ações de plantas
enum class PlantAction {
    COLLECT,    // Coletar
    MUTATE,     // Mutar
    FERTILIZE,  // Adubar
    WATER,      // Regar
    REPLANT,    // Replantar
    FEED        // Alimentar (só Dionaea)
};

// Cooldowns e tempos
const float COLLECT_TIME = 3.0f;
const float MUTATE_TIME = 4.0f;
const float FERTILIZE_TIME = 3.0f;
const float WATER_TIME = 2.0f;
const float REPLANT_COOLDOWN = 5.0f;
const float UV_LIGHT_DURATION = 5.0f;
const float OXYGEN_MASK_DURATION = 25.0f;
const float TOXIN_WARNING_TIME = 10.0f;

// Limites
const int MAX_PLANT_HEALTH = 100;
const int DIONAEA_FEED_LIMIT = 3;
const int MAX_EXPERIMENTS = 4;
const int MAX_PATIENTS = 5;

// Cores (Raylib)
#define COLOR_BACKGROUND (Color){20, 20, 30, 255}
#define COLOR_UI (Color){50, 50, 70, 255}
#define COLOR_TEXT (Color){220, 220, 220, 255}
#define COLOR_DANGER (Color){200, 50, 50, 255}
#define COLOR_SUCCESS (Color){50, 200, 50, 255}
#define COLOR_WARNING (Color){200, 200, 50, 255}

// Paths
const std::string SAVE_PATH = "saves/";
const std::string ASSETS_PATH = "assets/";

#endif // CONSTANTS_HPP