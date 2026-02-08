#include "UI/HackingMinigame.hpp"
#include "Utils/Constants.hpp"
#include <iostream>

HackingMinigame::HackingMinigame()
    : active(false),
      progress(0.0f),
      completed(false) {
    
    // Posição da barra de progresso (centro da tela)
    int barWidth = 500;
    int barHeight = 50;
    barBounds = {
        (float)(SCREEN_WIDTH / 2 - barWidth / 2),
        (float)(SCREEN_HEIGHT / 2 - barHeight / 2),
        (float)barWidth,
        (float)barHeight
    };
}

void HackingMinigame::Start() {
    active = true;
    progress = 0.0f;
    completed = false;
    
    std::cout << "[HACK] Minigame iniciado! Segure H para hackear..." << std::endl;
}

void HackingMinigame::Stop() {
    active = false;
}

void HackingMinigame::Update(float deltaTime) {
    if (!active || completed) return;
    
    // Jogador segura H para hackear
    if (IsKeyDown(KEY_H)) {
        progress += HACK_SPEED * deltaTime;
        
        if (progress >= 1.0f) {
            progress = 1.0f;
            completed = true;
            active = false;
            std::cout << "[HACK] Concluido! Jardim desbloqueado." << std::endl;
        }
    } else {
        // Soltar H faz perder progresso
        progress -= HACK_SPEED * deltaTime * 0.5f;
        if (progress < 0.0f) {
            progress = 0.0f;
        }
    }
}

void HackingMinigame::Render() {
    if (!active) return;
    
    // Escurecer fundo
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){0, 0, 0, 180});
    
    // Título
    const char* title = "HACKEAR PORTAS DO JARDIM";
    int titleWidth = MeasureText(title, 30);
    DrawText(title, SCREEN_WIDTH/2 - titleWidth/2, barBounds.y - 60, 30, COLOR_DANGER);
    
    // Instrução
    const char* instruction = "Segure H para hackear";
    int instrWidth = MeasureText(instruction, 20);
    DrawText(instruction, SCREEN_WIDTH/2 - instrWidth/2, barBounds.y - 30, 20, COLOR_TEXT);
    
    // Barra de fundo
    DrawRectangleRec(barBounds, DARKGRAY);
    
    // Barra de progresso
    fillBounds = barBounds;
    fillBounds.width = barBounds.width * progress;
    
    Color progressColor;
    if (progress < 0.3f) {
        progressColor = RED;
    } else if (progress < 0.7f) {
        progressColor = YELLOW;
    } else {
        progressColor = GREEN;
    }
    
    DrawRectangleRec(fillBounds, progressColor);
    
    // Bordas
    DrawRectangleLinesEx(barBounds, 3, COLOR_TEXT);
    
    // Porcentagem
    char percentText[16];
    sprintf(percentText, "%.0f%%", progress * 100);
    int percentWidth = MeasureText(percentText, 24);
    DrawText(percentText, SCREEN_WIDTH/2 - percentWidth/2, barBounds.y + 13, 24, WHITE);
    
    // Aviso se soltar
    if (!IsKeyDown(KEY_H) && progress > 0.0f) {
        const char* warning = "Perdendo progresso!";
        int warnWidth = MeasureText(warning, 18);
        DrawText(warning, SCREEN_WIDTH/2 - warnWidth/2, barBounds.y + 60, 18, COLOR_DANGER);
    }
}

void HackingMinigame::Reset() {
    active = false;
    progress = 0.0f;
    completed = false;
}