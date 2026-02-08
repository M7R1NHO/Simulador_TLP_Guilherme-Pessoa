#include "GameState.hpp"
#include <iostream>

GameState::GameState()
    : currentPhase(GamePhase::MENU),
      dayPhase(DayPhase::DUSK),
      currentDay(1),
      selectedPatient(0),
      gameWon(false),
      gameLost(false) {
}

void GameState::StartNewGame() {
    currentPhase = GamePhase::SELECTING_PATIENT;
    dayPhase = DayPhase::DUSK;
    currentDay = 1;
    selectedPatient = 0;
    gameWon = false;
    gameLost = false;
    
    std::cout << "[GAMESTATE] Novo jogo iniciado!" << std::endl;
}

void GameState::StartNewDay() {
    if (currentDay < TOTAL_DAYS) {
        currentDay++;
    }
    
    dayPhase = DayPhase::DUSK;
    currentPhase = GamePhase::SELECTING_PATIENT;
    selectedPatient = 0;
    
    std::cout << "[GAMESTATE] Dia " << currentDay << " iniciado." << std::endl;
}

void GameState::CompleteDay() {
    std::cout << "[GAMESTATE] Dia " << currentDay << " completo!" << std::endl;
    
    // Verificar se é o último dia
    if (IsLastDay()) {
        gameWon = true;
        currentPhase = GamePhase::GAME_OVER;
        std::cout << "[GAMESTATE] JOGO COMPLETO! VITORIA!" << std::endl;
    } else {
        // Próximo dia
        StartNewDay();
    }
}

void GameState::TransitionToDusk() {
    dayPhase = DayPhase::DUSK;
    currentPhase = GamePhase::SELECTING_PATIENT;
    
    std::cout << "[GAMESTATE] Fase: ANOITECER" << std::endl;
}

void GameState::TransitionToNight() {
    dayPhase = DayPhase::NIGHT;
    currentPhase = GamePhase::NIGHT_PHASE;
    
    std::cout << "[GAMESTATE] Fase: NOITE (6 minutos)" << std::endl;
}

bool GameState::CanProgressToNextDay() const {
    // Verifica se pode avançar para o próximo dia
    // (geralmente após completar receita)
    return selectedPatient > 0;
}