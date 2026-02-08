#include "Entities/Planta.hpp"
#include <cmath>

Planta::Planta(PlantType plantType, Vector2 pos) 
    : type(plantType), 
      mutationState(MutationState::NORMAL),
      health(MAX_PLANT_HEALTH),
      isAlive(true),
      actionTimer(0.0f),
      isProcessing(false),
      position(pos),
      canBeMutated(true),
      replantCooldown(0) {
}

void Planta::Update(float deltaTime) {
    if (!isAlive && replantCooldown > 0) {
        replantCooldown -= deltaTime;
    }
    
    if (isProcessing && actionTimer > 0) {
        actionTimer -= deltaTime;
        if (actionTimer <= 0) {
            isProcessing = false;
        }
    }
}

void Planta::Render() {
    if (!isAlive) {
        DrawCircleV(position, 30, GRAY);
        DrawText("MORTA", position.x - 25, position.y - 10, 12, DARKGRAY);
        return;
    }
    
    // Cor baseada no estado
    Color plantColor = GREEN;
    switch (mutationState) {
        case MutationState::NORMAL:
            plantColor = GREEN;
            break;
        case MutationState::FERTILIZED:
            plantColor = (Color){100, 200, 100, 255};
            break;
        case MutationState::MUTANT:
            plantColor = (Color){200, 100, 200, 255};
            break;
        case MutationState::MUTANT_FERTILIZED:
            plantColor = (Color){150, 100, 200, 255};
            break;
    }
    
    // Desenha a planta
    DrawCircleV(position, 35, plantColor);
    
    // Barra de vida
    float healthPercent = (float)health / MAX_PLANT_HEALTH;
    DrawRectangle(position.x - 40, position.y - 50, 80, 8, DARKGRAY);
    DrawRectangle(position.x - 40, position.y - 50, 80 * healthPercent, 8, 
                  healthPercent > 0.5f ? GREEN : (healthPercent > 0.25f ? YELLOW : RED));
    
    // Timer de ação
    if (isProcessing) {
        DrawCircleSector(position, 40, 0, 360 * (1.0f - actionTimer / 5.0f), 16, 
                        (Color){255, 255, 0, 100});
    }
}

void Planta::ProcessAction(PlantAction action) {
    if (isProcessing || !isAlive) return;
    
    isProcessing = true;
    
    switch (action) {
        case PlantAction::COLLECT:
            actionTimer = COLLECT_TIME;
            break;
        case PlantAction::MUTATE:
            actionTimer = MUTATE_TIME;
            break;
        case PlantAction::FERTILIZE:
            actionTimer = FERTILIZE_TIME;
            break;
        case PlantAction::WATER:
            actionTimer = WATER_TIME;
            Heal(30);
            break;
        default:
            isProcessing = false;
            break;
    }
}

void Planta::TakeDamage(int damage) {
    health -= damage;
    if (health <= 0) {
        health = 0;
        Kill();
    }
}

void Planta::Heal(int amount) {
    if (isAlive) {
        health += amount;
        if (health > MAX_PLANT_HEALTH) {
            health = MAX_PLANT_HEALTH;
        }
    }
}

void Planta::SetMutationState(MutationState state) {
    mutationState = state;
}

void Planta::Kill() {
    isAlive = false;
    replantCooldown = REPLANT_COOLDOWN;
    mutationState = MutationState::NORMAL;
}

void Planta::Replant() {
    if (!isAlive && replantCooldown <= 0) {
        isAlive = true;
        health = MAX_PLANT_HEALTH;
        mutationState = MutationState::NORMAL;
    }
}

std::string Planta::GetIngredientName() {
    std::string baseName;
    switch (type) {
        case PlantType::DROSERA: baseName = "Drosera"; break;
        case PlantType::DIONAEA: baseName = "Dionaea"; break;
        case PlantType::NICOTIANA: baseName = "Nicotiana"; break;
        case PlantType::FRND19: baseName = "F-R.N.D.19"; break;
        case PlantType::PAPOULA: baseName = "Papoula"; break;
        default: baseName = "Desconhecido"; break;
    }
    
    switch (mutationState) {
        case MutationState::FERTILIZED:
            return baseName + " Adubada";
        case MutationState::MUTANT:
            return baseName + " Mutante";
        case MutationState::MUTANT_FERTILIZED:
            return baseName + " Mutante Adubada";
        default:
            return baseName;
    }
}

bool Planta::CanCollect() const {
    return isAlive && !isProcessing;
}

bool Planta::CanMutate() const {
    return isAlive && !isProcessing && canBeMutated;
}

bool Planta::CanFertilize() const {
    return isAlive && !isProcessing;
}