#include "Entities/Nicotiana.hpp"
#include "Entities/Experimento.hpp"
#include <iostream>

Nicotiana::Nicotiana(Vector2 pos)
    : Planta(PlantType::NICOTIANA, pos),
      isProducingToxin(false),
      toxinTimer(0.0f),
      toxinWarningTimer(0.0f) {
}

void Nicotiana::Update(float deltaTime) {
    Planta::Update(deltaTime);
    
    if (!isAlive) {
        isProducingToxin = false;
        return;
    }
    
    // Se está mutante, produz toxina
    isProducingToxin = (mutationState == MutationState::MUTANT || 
                        mutationState == MutationState::MUTANT_FERTILIZED);
}

void Nicotiana::Render() {
    Planta::Render();
    
    // Indicador de toxina
    if (isProducingToxin) {
        // Efeito de "fumaça" verde pulsante
        int alpha = (int)(100 + 155 * abs(sin(GetTime() * 3)));
        Color toxinColor = {100, 255, 100, (unsigned char)alpha};
        
        DrawCircleV(position, 50, toxinColor);
        DrawText("TOXINA", position.x - 30, position.y - 70, 12, COLOR_DANGER);
    }
}

void Nicotiana::ProcessAction(PlantAction action) {
    Planta::ProcessAction(action);
}

void Nicotiana::OnMutate() {
    isProducingToxin = true;
    std::cout << "[NICOTIANA] Mutante! Produzindo toxina..." << std::endl;
    std::cout << "[AVISO] Efeito: Stress -3/s (Exp 1,2) | Irritacao +2/s (Exp 3,4)" << std::endl;
}

void Nicotiana::OnDemutate() {
    isProducingToxin = false;
    std::cout << "[NICOTIANA] Voltou ao normal. Toxina parou." << std::endl;
}

void Nicotiana::ApplyToxinEffects(std::vector<std::unique_ptr<Experimento>>& experiments, float deltaTime) {
    if (!isProducingToxin || !isAlive) return;
    
    for (auto& exp : experiments) {
        exp->ApplyNicotianaToxin(deltaTime);
    }
}

bool Nicotiana::ShouldWarnPlayer() const {
    return isProducingToxin && isAlive;
}