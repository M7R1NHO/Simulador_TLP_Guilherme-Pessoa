#include "Systems/TimeSystem.hpp"
#include <iostream>

TimeSystem::TimeSystem()
    : nightTimer(NIGHT_DURATION_SECONDS),
      totalGameTime(0.0f),
      isPaused(false) {
}

void TimeSystem::Update(float deltaTime) {
    if (isPaused) return;
    
    // Atualizar timer da noite
    if (nightTimer > 0.0f) {
        nightTimer -= deltaTime;
        
        if (nightTimer <= 0.0f) {
            nightTimer = 0.0f;
            std::cout << "[TEMPO] Noite terminada!" << std::endl;
        }
    }
    
    // Tempo total de jogo
    totalGameTime += deltaTime;
}

void TimeSystem::Reset() {
    nightTimer = NIGHT_DURATION_SECONDS;
    totalGameTime = 0.0f;
    isPaused = false;
}

void TimeSystem::ResetNight() {
    nightTimer = NIGHT_DURATION_SECONDS;
    std::cout << "[TEMPO] Timer da noite resetado (6 minutos)" << std::endl;
}

void TimeSystem::GetFormattedTime(int& minutes, int& seconds) const {
    minutes = (int)(nightTimer / 60.0f);
    seconds = (int)nightTimer % 60;
}