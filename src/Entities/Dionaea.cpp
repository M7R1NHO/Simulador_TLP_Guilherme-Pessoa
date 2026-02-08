#include "Entities/Dionaea.hpp"
#include <iostream>

Dionaea::Dionaea(Vector2 pos) 
    : Planta(PlantType::DIONAEA, pos),
      attackCooldown(15.0f),
      attackTimer(15.0f),
      damagePerAttack(20),
      isFed(false),
      feedCount(0) {
    
    mutationState = MutationState::MUTANT;
}

void Dionaea::Update(float deltaTime) {
    Planta::Update(deltaTime);
    
    if (!isAlive) return;
    
    if (attackTimer > 0) {
        attackTimer -= deltaTime;
    }
}

void Dionaea::Render() {
    Planta::Render();
    
    // Barra de ataque
    float attackPercent = 1.0f - (attackTimer / attackCooldown);
    Color attackColor = attackPercent < 0.7f ? YELLOW : COLOR_DANGER;
    
    DrawRectangle(position.x - 40, position.y + 45, 80, 6, DARKGRAY);
    DrawRectangle(position.x - 40, position.y + 45, 80 * attackPercent, 6, attackColor);
    
    // Indicador de ataques disponíveis
    if (CanAttack()) {
        DrawText("!", position.x + 35, position.y - 35, 24, RED);
    }
    
    // Contador de alimentações
    DrawText(TextFormat("Alim: %d/%d", feedCount, MAX_FEEDS), 
             position.x - 35, position.y + 55, 12, COLOR_TEXT);
}

void Dionaea::ProcessAction(PlantAction action) {
    if (!isAlive) return;
    
    if (action == PlantAction::FEED) {
        Feed();
    } else {
        Planta::ProcessAction(action);
    }
}

void Dionaea::AttackNearbyPlants(std::vector<std::unique_ptr<Planta>>& allPlants) {
    if (!CanAttack()) return;
    
    int plantsAttacked = 0;
    for (auto& plant : allPlants) {
        if (plant->GetType() == PlantType::DIONAEA) continue;
        
        if (plant->IsAlive()) {
            plant->TakeDamage(damagePerAttack);
            plantsAttacked++;
        }
    }
    
    attackTimer = attackCooldown;
    
    if (plantsAttacked > 0) {
        std::cout << "Dionaea atacou " << plantsAttacked << " plantas! (-" 
                  << damagePerAttack << " HP)" << std::endl;
    }
}

bool Dionaea::CanAttack() const {
    return isAlive && attackTimer <= 0;
}

void Dionaea::Feed() {
    if (feedCount >= MAX_FEEDS) {
        std::cout << "Dionaea: Limite de alimentacoes atingido!" << std::endl;
        return;
    }
    
    attackTimer = attackCooldown;
    feedCount++;
    isFed = true;
    
    std::cout << "Dionaea alimentada! Timer de ataque resetado. (" 
              << feedCount << "/" << MAX_FEEDS << ")" << std::endl;
}