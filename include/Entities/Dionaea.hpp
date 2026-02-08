#ifndef DIONAEA_HPP
#define DIONAEA_HPP

#include "Entities/Planta.hpp"
#include <vector>
#include <memory>

class Dionaea : public Planta {
private:
    float attackCooldown;
    float attackTimer;
    int damagePerAttack;
    bool isFed;
    int feedCount;
    const int MAX_FEEDS = 3;

public:
    Dionaea(Vector2 pos);
    
    void Update(float deltaTime) override;
    void Render() override;
    void ProcessAction(PlantAction action) override;
    
    // Atacar outras plantas
    void AttackNearbyPlants(std::vector<std::unique_ptr<Planta>>& allPlants);
    bool CanAttack() const;
    
    // Alimentar para resetar cooldown
    void Feed();
    bool CanBeFed() const { return feedCount < MAX_FEEDS; }
    int GetFeedCount() const { return feedCount; }
};

#endif // DIONAEA_HPP