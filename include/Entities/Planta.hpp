#ifndef PLANTA_HPP
#define PLANTA_HPP

#include "Utils/Constants.hpp"
#include "raylib.h"
#include <string>

class Planta {
protected:
    PlantType type;
    MutationState mutationState;
    int health;
    bool isAlive;
    float actionTimer;
    bool isProcessing;
    Vector2 position;
    
    // Flags específicas
    bool canBeMutated;
    int replantCooldown;

public:
    Planta(PlantType plantType, Vector2 pos);
    virtual ~Planta() = default;
    
    // Métodos principais
    virtual void Update(float deltaTime);
    virtual void Render();
    virtual void ProcessAction(PlantAction action);
    
    // Getters
    PlantType GetType() const { return type; }
    MutationState GetMutationState() const { return mutationState; }
    int GetHealth() const { return health; }
    bool IsAlive() const { return isAlive; }
    bool IsProcessing() const { return isProcessing; }
    bool CanBeMutated() const { return canBeMutated; }
    Vector2 GetPosition() const { return position; }
    
    // Setters
    void TakeDamage(int damage);
    void Heal(int amount);
    void SetMutationState(MutationState state);
    void Kill();
    void Replant();
    
    // Métodos virtuais para override
    virtual void OnMutate() {}
    virtual void OnDemutate() {}
    virtual std::string GetIngredientName();
    
    // Verificações
    bool CanCollect() const;
    bool CanMutate() const;
    bool CanFertilize() const;
};

#endif // PLANTA_HPP