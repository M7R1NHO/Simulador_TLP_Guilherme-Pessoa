#include "Entities/Drosera.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

Drosera::Drosera(Vector2 pos) 
    : Planta(PlantType::DROSERA, pos),
      canBePlayerMutated(false),
      isRareStateActive(false),
      rareStateTimer(0.0f),
      hasBeenFertilizedInRareState(false) {
    
    canBeMutated = false;
}

void Drosera::Update(float deltaTime) {
    Planta::Update(deltaTime);
    
    if (!isAlive) return;
    
    // Chance aleatória de ativar estado raro (5% por segundo)
    if (!isRareStateActive && mutationState == MutationState::NORMAL) {
        if ((rand() % 100) < 5) {
            ActivateRareState();
        }
    }
    
    // Timer do estado raro
    if (isRareStateActive) {
        rareStateTimer -= deltaTime;
        if (rareStateTimer <= 0) {
            isRareStateActive = false;
            if (mutationState == MutationState::MUTANT && !hasBeenFertilizedInRareState) {
                mutationState = MutationState::NORMAL;
            }
        }
    }
}

void Drosera::Render() {
    Planta::Render();
    
    // Indicador visual de estado raro
    if (isRareStateActive) {
        int alpha = (int)(128 + 127 * sin(GetTime() * 5));
        Color glowColor = {255, 215, 0, (unsigned char)alpha};
        DrawCircleV(position, 45, glowColor);
        
        DrawText("RARO!", position.x - 25, position.y + 55, 14, GOLD);
        
        int timeLeft = (int)rareStateTimer;
        DrawText(TextFormat("%ds", timeLeft), position.x - 10, position.y + 70, 12, GOLD);
    }
    
    // Indicador de bloqueio de mutação
    if (BlocksMutation()) {
        DrawText("BLOQUEIO", position.x - 35, position.y - 65, 12, COLOR_DANGER);
    }
}

void Drosera::ProcessAction(PlantAction action) {
    if (!isAlive) return;
    
    switch (action) {
        case PlantAction::MUTATE:
            // Drosera não pode ser mutada pelo jogador
            break;
            
        case PlantAction::FERTILIZE:
            if (isRareStateActive && mutationState == MutationState::MUTANT) {
                if (!hasBeenFertilizedInRareState) {
                    isProcessing = true;
                    actionTimer = FERTILIZE_TIME;
                    hasBeenFertilizedInRareState = true;
                    mutationState = MutationState::MUTANT_FERTILIZED;
                }
            }
            break;
            
        default:
            Planta::ProcessAction(action);
            break;
    }
}

void Drosera::OnMutate() {
    std::cout << "Drosera entrou em estado mutante! Mutacoes bloqueadas!" << std::endl;
}

void Drosera::OnDemutate() {
    std::cout << "Drosera retornou ao normal. Mutacoes liberadas." << std::endl;
}

void Drosera::ActivateRareState() {
    isRareStateActive = true;
    rareStateTimer = 30.0f;
    mutationState = MutationState::MUTANT;
    OnMutate();
    
    std::cout << "ESTADO RARO: Drosera pode ser adubada!" << std::endl;
}

bool Drosera::CanFertilizeInRareState() const {
    return isRareStateActive && 
           mutationState == MutationState::MUTANT && 
           !hasBeenFertilizedInRareState;
}

bool Drosera::BlocksMutation() const {
    return mutationState == MutationState::MUTANT && isAlive;
}