#include "Game.hpp"
#include "Entities/Drosera.hpp"
#include "Entities/Dionaea.hpp"
#include <iostream>

Game::Game() 
    : currentPhase(GamePhase::MENU),
      dayPhase(DayPhase::DUSK),
      currentDay(1),
      nightTimer(NIGHT_DURATION),
      isPaused(false),
      gameTime(0.0f),
      showMenu(true),
      showPatientSelection(false),
      selectedPatient(-1),
      oxygenMaskActive(false),
      oxygenMaskTimer(0.0f),
      uvLightActive(false),
      uvLightTimer(0.0f),
      toxinWarning(false),
      toxinWarningTimer(0.0f),
      dionaeaFeedCount(0),
      recipeStep(0) {
}

Game::~Game() {
}

void Game::Initialize() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Mutant Facility - Survival Game");
    SetTargetFPS(FPS);
    
    camera.target = (Vector2){ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
    camera.offset = (Vector2){ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    
    InitializePlants();
    InitializeExperiments();
    
    std::cout << "Jogo inicializado com sucesso!" << std::endl;
}

void Game::InitializePlants() {
    Vector2 plantPositions[6] = {
        {200, 300},
        {400, 300},
        {600, 300},
        {200, 500},
        {400, 500},
        {600, 500}
    };
    
    plants.push_back(std::make_unique<Drosera>(plantPositions[0]));
    plants.push_back(std::make_unique<Dionaea>(plantPositions[1]));
    plants.push_back(std::make_unique<Planta>(PlantType::NICOTIANA, plantPositions[2]));
    plants.push_back(std::make_unique<Planta>(PlantType::FRND19, plantPositions[3]));
    plants.push_back(std::make_unique<Planta>(PlantType::PAPOULA, plantPositions[4]));
}

void Game::InitializeExperiments() {
    Vector2 experimentPositions[4] = {
        {900, 200},
        {1100, 200},
        {900, 400},
        {1100, 400}
    };
    
    for (int i = 0; i < 4; i++) {
        experiments.push_back(std::make_unique<Experimento>(i + 1, experimentPositions[i]));
    }
}

void Game::Run() {
    while (!WindowShouldClose()) {
        Update();
        Render();
    }
}

void Game::Update() {
    deltaTime = GetFrameTime();
    gameTime += deltaTime;
    
    if (!isPaused) {
        switch (currentPhase) {
            case GamePhase::MENU:
                UpdateMenu();
                break;
            case GamePhase::SELECTING_PATIENT:
                UpdatePatientSelection();
                break;
            case GamePhase::NIGHT_PHASE:
                UpdateNightPhase();
                break;
            default:
                break;
        }
    }
    
    HandleInput();
}

void Game::UpdateMenu() {
    if (IsKeyPressed(KEY_ENTER)) {
        currentPhase = GamePhase::SELECTING_PATIENT;
        showMenu = false;
        showPatientSelection = true;
    }
}

void Game::UpdatePatientSelection() {
    if (IsKeyPressed(KEY_ONE)) selectedPatient = 1;
    if (IsKeyPressed(KEY_TWO)) selectedPatient = 2;
    if (IsKeyPressed(KEY_THREE)) selectedPatient = 3;
    if (IsKeyPressed(KEY_FOUR)) selectedPatient = 4;
    if (IsKeyPressed(KEY_FIVE)) selectedPatient = 5;
    
    if (selectedPatient > 0 && IsKeyPressed(KEY_ENTER)) {
        LoadPatientRecipe(selectedPatient);
        currentPhase = GamePhase::NIGHT_PHASE;
        dayPhase = DayPhase::NIGHT;
        showPatientSelection = false;
    }
}

void Game::UpdateNightPhase() {
    nightTimer -= deltaTime;
    
    if (nightTimer <= 0) {
        CompleteDay();
        return;
    }
    
    UpdatePlants();
    UpdateExperiments();
    UpdateContainment();
    CheckToxins();
}

void Game::UpdatePlants() {
    for (auto& plant : plants) {
        plant->Update(deltaTime);
    }
    
    // Dionaea ataca
    if (plants.size() > 1) {
        Dionaea* dionaea = dynamic_cast<Dionaea*>(plants[1].get());
        if (dionaea && dionaea->CanAttack()) {
            dionaea->AttackNearbyPlants(plants);
        }
    }
}

void Game::UpdateExperiments() {
    for (auto& experiment : experiments) {
        experiment->Update(deltaTime);
        
        if (plants.size() > 2 && plants[2]->GetMutationState() == MutationState::MUTANT) {
            experiment->ApplyNicotianaToxin(deltaTime);
        }
        
        if (plants.size() > 4 && plants[4]->GetMutationState() == MutationState::MUTANT) {
            experiment->ApplyPapoulaToxin(deltaTime);
        }
    }
}

void Game::UpdateContainment() {
    if (oxygenMaskActive) {
        oxygenMaskTimer -= deltaTime;
        if (oxygenMaskTimer <= 0) {
            oxygenMaskActive = false;
        }
    }
    
    if (uvLightActive) {
        uvLightTimer -= deltaTime;
        if (uvLightTimer <= 0) {
            uvLightActive = false;
            if (plants.size() > 0 && plants[0]->GetMutationState() == MutationState::MUTANT) {
                plants[0]->SetMutationState(MutationState::NORMAL);
            }
        }
    }
}

void Game::CheckToxins() {
    bool toxinActive = false;
    if (plants.size() > 2 && plants[2]->GetMutationState() == MutationState::MUTANT) toxinActive = true;
    if (plants.size() > 4 && plants[4]->GetMutationState() == MutationState::MUTANT) toxinActive = true;
    
    if (toxinActive && !oxygenMaskActive) {
        if (!toxinWarning) {
            toxinWarning = true;
            toxinWarningTimer = TOXIN_WARNING_TIME;
        } else {
            toxinWarningTimer -= deltaTime;
            if (toxinWarningTimer <= 0) {
                std::cout << "GAME OVER: Intoxicacao!" << std::endl;
                currentPhase = GamePhase::GAME_OVER;
            }
        }
    } else {
        toxinWarning = false;
        toxinWarningTimer = 0;
    }
}

void Game::HandleInput() {
    if (IsKeyPressed(KEY_P)) {
        isPaused = !isPaused;
    }
    
    if (currentPhase == GamePhase::NIGHT_PHASE) {
        if (IsKeyPressed(KEY_M)) {
            oxygenMaskActive = true;
            oxygenMaskTimer = OXYGEN_MASK_DURATION;
            toxinWarning = false;
        }
        
        if (IsKeyPressed(KEY_U)) {
            uvLightActive = true;
            uvLightTimer = UV_LIGHT_DURATION;
        }
    }
}

void Game::Render() {
    BeginDrawing();
    ClearBackground(COLOR_BACKGROUND);
    
    switch (currentPhase) {
        case GamePhase::MENU:
            RenderMenu();
            break;
        case GamePhase::SELECTING_PATIENT:
            RenderPatientSelection();
            break;
        case GamePhase::NIGHT_PHASE:
            RenderNightPhase();
            break;
        case GamePhase::GAME_OVER:
            DrawText("GAME OVER", SCREEN_WIDTH/2 - 150, SCREEN_HEIGHT/2 - 30, 60, RED);
            DrawText("Pressione ESC para sair", SCREEN_WIDTH/2 - 150, SCREEN_HEIGHT/2 + 50, 20, WHITE);
            break;
        default:
            break;
    }
    
    EndDrawing();
}

void Game::RenderMenu() {
    DrawText("MUTANT FACILITY", SCREEN_WIDTH/2 - 200, 200, 60, COLOR_TEXT);
    DrawText("Survival Game", SCREEN_WIDTH/2 - 120, 280, 30, COLOR_TEXT);
    DrawText("Pressione ENTER para comecar", SCREEN_WIDTH/2 - 200, 400, 25, GREEN);
    DrawText("M - Mascara | U - Luz UV | P - Pausar", 50, 650, 16, GRAY);
}

void Game::RenderPatientSelection() {
    DrawText("SELECIONE O PACIENTE DO DIA", SCREEN_WIDTH/2 - 250, 100, 35, COLOR_TEXT);
    DrawText(("Dia " + std::to_string(currentDay) + " de " + std::to_string(TOTAL_DAYS)).c_str(), 
             SCREEN_WIDTH/2 - 60, 160, 25, COLOR_WARNING);
    
    for (int i = 1; i <= MAX_PATIENTS; i++) {
        int yPos = 220 + (i - 1) * 80;
        Color bgColor = (i == selectedPatient) ? COLOR_SUCCESS : COLOR_UI;
        
        DrawRectangle(SCREEN_WIDTH/2 - 300, yPos, 600, 60, bgColor);
        DrawRectangleLines(SCREEN_WIDTH/2 - 300, yPos, 600, 60, COLOR_TEXT);
        
        std::string patientText = std::to_string(i) + " - Paciente " + std::to_string(i);
        DrawText(patientText.c_str(), SCREEN_WIDTH/2 - 280, yPos + 20, 24, COLOR_TEXT);
    }
}

void Game::RenderNightPhase() {
    BeginMode2D(camera);
    
    DrawText("PLANTAS", 100, 200, 24, COLOR_TEXT);
    for (auto& plant : plants) {
        plant->Render();
    }
    
    DrawText("EXPERIMENTOS", 800, 100, 24, COLOR_TEXT);
    for (auto& experiment : experiments) {
        experiment->Render();
    }
    
    EndMode2D();
    
    RenderHUD();
    RenderTimer();
    RenderInventory();
    RenderWarnings();
    
    if (isPaused) {
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){0, 0, 0, 150});
        DrawText("PAUSADO", SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 30, 50, COLOR_TEXT);
    }
}

void Game::RenderHUD() {
    DrawRectangle(0, 0, SCREEN_WIDTH, 60, COLOR_UI);
    DrawText(("Dia " + std::to_string(currentDay)).c_str(), 20, 20, 24, COLOR_TEXT);
    DrawText(("Paciente: " + std::to_string(selectedPatient)).c_str(), 150, 20, 24, COLOR_TEXT);
}

void Game::RenderTimer() {
    int minutes = (int)(nightTimer / 60);
    int seconds = (int)nightTimer % 60;
    
    char timeStr[32];
    sprintf(timeStr, "Tempo: %02d:%02d", minutes, seconds);
    
    Color timerColor = nightTimer < 60 ? COLOR_DANGER : (nightTimer < 180 ? COLOR_WARNING : COLOR_TEXT);
    DrawText(timeStr, SCREEN_WIDTH - 200, 20, 24, timerColor);
}

void Game::RenderInventory() {
    DrawRectangle(10, SCREEN_HEIGHT - 150, 300, 140, COLOR_UI);
    DrawRectangleLines(10, SCREEN_HEIGHT - 150, 300, 140, COLOR_TEXT);
    DrawText("INVENTARIO", 20, SCREEN_HEIGHT - 145, 18, COLOR_TEXT);
    
    int yOffset = 0;
    for (size_t i = 0; i < inventory.size() && i < 5; i++) {
        DrawText(inventory[i].c_str(), 20, SCREEN_HEIGHT - 115 + yOffset, 14, COLOR_TEXT);
        yOffset += 20;
    }
}

void Game::RenderWarnings() {
    if (toxinWarning) {
        DrawRectangle(SCREEN_WIDTH/2 - 200, 100, 400, 60, COLOR_DANGER);
        DrawText("INALANDO TOXINA!", SCREEN_WIDTH/2 - 150, 110, 30, WHITE);
        DrawText(("Tempo: " + std::to_string((int)toxinWarningTimer) + "s").c_str(), 
                 SCREEN_WIDTH/2 - 80, 140, 20, WHITE);
    }
    
    if (oxygenMaskActive) {
        DrawRectangle(SCREEN_WIDTH - 220, 70, 200, 40, (Color){50, 100, 200, 200});
        DrawText(("Oxigenio: " + std::to_string((int)oxygenMaskTimer) + "s").c_str(), 
                 SCREEN_WIDTH - 210, 80, 20, WHITE);
    }
    
    if (uvLightActive) {
        DrawRectangle(SCREEN_WIDTH - 220, 120, 200, 40, (Color){200, 100, 200, 200});
        DrawText(("Luz UV: " + std::to_string((int)uvLightTimer) + "s").c_str(), 
                 SCREEN_WIDTH - 210, 130, 20, WHITE);
    }
}

void Game::StartNewDay() {
    currentDay++;
    nightTimer = NIGHT_DURATION;
    currentPhase = GamePhase::SELECTING_PATIENT;
    inventory.clear();
    recipeStep = 0;
}

void Game::CompleteDay() {
    if (CheckRecipeCompletion()) {
        if (currentDay >= TOTAL_DAYS) {
            currentPhase = GamePhase::GAME_OVER;
            std::cout << "VITORIA!" << std::endl;
        } else {
            StartNewDay();
        }
    } else {
        currentPhase = GamePhase::GAME_OVER;
    }
}

void Game::LoadPatientRecipe(int patientId) {
    currentRecipe.clear();
    switch (patientId) {
        case 1: currentRecipe = {"Nicotiana", "Drosera Mutante", "Papoula Adubada"}; break;
        case 2: currentRecipe = {"F-R.N.D.19 Mutante", "Dionaea", "Nicotiana Adubada"}; break;
        case 3: currentRecipe = {"Papoula Mutante", "Drosera", "F-R.N.D.19 Adubada"}; break;
        case 4: currentRecipe = {"Nicotiana Mutante Adubada", "Papoula", "Drosera Mutante"}; break;
        case 5: currentRecipe = {"Dionaea", "F-R.N.D.19 Mutante Adubada", "Nicotiana Mutante"}; break;
    }
}

bool Game::CheckRecipeCompletion() {
    return recipeStep >= (int)currentRecipe.size();
}

void Game::Shutdown() {
    CloseWindow();
}