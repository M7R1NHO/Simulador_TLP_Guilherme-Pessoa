#include "Entities/FRND19.hpp"
#include <iostream>

FRND19::FRND19(Vector2 pos)
    : Planta(PlantType::FRND19, pos),
      isBlockingSuperior(false) {
}

void FRND19::Update(float deltaTime) {
    Planta::Update(deltaTime);
    
    if (!isAlive) {
        isBlockingSuperior = false;
        return;
    }
    
    // Se está mutante, bloqueia Superior
    isBlockingSuperior = (mutationState == MutationState::MUTANT || 
                          mutationState == MutationState::MUTANT_FERTILIZED);
}

void FRND19::Render() {
    Planta::Render();
    
    // Indicador de bloqueio
    if (isBlockingSuperior) {
        // Escudo azul pulsante
        int alpha = (int)(150 + 105 * abs(sin(GetTime() * 2)));
        Color shieldColor = {50, 150, 255, (unsigned char)alpha};
        
        DrawCircleLines(position.x, position.y, 55, shieldColor);
        DrawCircleLines(position.x, position.y, 60, shieldColor);
        
        DrawText("BLOQUEIO", position.x - 35, position.y - 75, 11, (Color){50, 150, 255, 255});
        DrawText("SUPERIOR", position.x - 35, position.y - 65, 11, (Color){50, 150, 255, 255});
    }
}

void FRND19::ProcessAction(PlantAction action) {
    Planta::ProcessAction(action);
}

void FRND19::OnMutate() {
    isBlockingSuperior = true;
    std::cout << "[F-R.N.D.19] Mutante! Bloqueando 'Pane Geral' do Superior!" << std::endl;
    std::cout << "[INFO] O Superior nao podera usar 'Pane Geral' ate o fim do dia." << std::endl;
}

void FRND19::OnDemutate() {
    isBlockingSuperior = false;
    std::cout << "[F-R.N.D.19] Voltou ao normal. Bloqueio desativado." << std::endl;
}