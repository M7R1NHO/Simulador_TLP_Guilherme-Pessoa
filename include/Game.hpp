#ifndef GAME_HPP
#define GAME_HPP

#include "raylib.h"
#include "Utils/Constants.hpp"
#include "Entities/Planta.hpp"
#include "Entities/Experimento.hpp"
#include <vector>
#include <memory>

class Game {
private:
    // Estado do jogo
    GamePhase currentPhase;
    DayPhase dayPhase;
    int currentDay;
    float nightTimer;
    bool isPaused;
    
    // Entidades
    std::vector<std::unique_ptr<Planta>> plants;
    std::vector<std::unique_ptr<Experimento>> experiments;
    
    // Sistema de tempo
    float gameTime;
    float deltaTime;
    
    // UI State
    bool showMenu;
    bool showPatientSelection;
    int selectedPatient;
    
    // Máscaras e contenção
    bool oxygenMaskActive;
    float oxygenMaskTimer;
    bool uvLightActive;
    float uvLightTimer;
    bool toxinWarning;
    float toxinWarningTimer;
    
    // Dionaea feed counter
    int dionaeaFeedCount;
    
    // Inventário
    std::vector<std::string> inventory;
    std::vector<std::string> currentRecipe;
    int recipeStep;
    
    // Camera
    Camera2D camera;

public:
    Game();
    ~Game();
    
    void Initialize();
    void Run();
    void Shutdown();
    
private:
    void Update();
    void Render();
    void HandleInput();
    
    // Fases do jogo
    void UpdateMenu();
    void UpdatePatientSelection();
    void UpdateNightPhase();
    void RenderMenu();
    void RenderPatientSelection();
    void RenderNightPhase();
    
    // Sistemas
    void UpdatePlants();
    void UpdateExperiments();
    void UpdateContainment();
    void CheckToxins();
    
    // UI
    void RenderHUD();
    void RenderTimer();
    void RenderInventory();
    void RenderWarnings();
    
    // Utilidades
    void StartNewDay();
    void CompleteDay();
    void LoadPatientRecipe(int patientId);
    bool CheckRecipeCompletion();
    
    // Inicialização
    void InitializePlants();
    void InitializeExperiments();
};

#endif // GAME_HPP