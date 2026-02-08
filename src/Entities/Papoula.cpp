#include "Entities/Papoula.hpp"
#include "Entities/Experimento.hpp"
#include <iostream>

Papoula::Papoula(Vector2 pos)
    : Planta(PlantType::PAPOULA, pos),
      isProducingToxin(false) {
}

void Papoula::Update(float deltaTime) {
    Planta::Update(deltaTime);
    
    if (!isAlive) {
        isProducingToxin = false;
        return;
    }
    
    // Se está mutante, produz toxina
    isProducingToxin = (mutationState == MutationState::MUTANT || 
                        mutationState == MutationState::MUTANT_FERTILIZED);
}

void Papoula::Render() {
    Planta::Render();
    
    // Indicador de toxina (diferente da Nicotiana)
    if (isProducingToxin) {
        // Efeito de "névoa" roxa pulsante
        int alpha = (int)(100 + 155 * abs(sin(GetTime() * 2.5)));
        Color toxinColor = {200, 100, 255, (unsigned char)alpha};
        
        DrawCircleV(position, 50, toxinColor);
        DrawText("TOXINA", position.x - 30, position.y - 70, 12, COLOR_DANGER);
    }
}

void Papoula::ProcessAction(PlantAction action) {
    Planta::ProcessAction(action);
}

void Papoula::OnMutate() {
    isProducingToxin = true;
    std::cout << "[PAPOULA] Mutante! Produzindo toxina..." << std::endl;
    std::cout << "[AVISO] Efeito: Stress -3/s (Exp 3,4) | Irritacao +2/s (Exp 1,2)" << std::endl;
}

void Papoula::OnDemutate() {
    isProducingToxin = false;
    std::cout << "[PAPOULA] Voltou ao normal. Toxina parou." << std::endl;
}

void Papoula::ApplyToxinEffects(std::vector<std::unique_ptr<Experimento>>& experiments, float deltaTime) {
    if (!isProducingToxin || !isAlive) return;
    
    for (auto& exp : experiments) {
        exp->ApplyPapoulaToxin(deltaTime);
    }
}

bool Papoula::ShouldWarnPlayer() const {
    return isProducingToxin && isAlive;
}