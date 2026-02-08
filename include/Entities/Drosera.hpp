#ifndef DROSERA_HPP
#define DROSERA_HPP

#include "Entities/Planta.hpp"

class Drosera : public Planta {
private:
    bool canBePlayerMutated;
    bool isRareStateActive;
    float rareStateTimer;
    bool hasBeenFertilizedInRareState;

public:
    Drosera(Vector2 pos);
    
    void Update(float deltaTime) override;
    void Render() override;
    void ProcessAction(PlantAction action) override;
    
    void OnMutate() override;
    void OnDemutate() override;
    
    // Estado raro
    void ActivateRareState();
    bool IsInRareState() const { return isRareStateActive; }
    bool CanFertilizeInRareState() const;
    
    // Bloqueia mutação de outras plantas
    bool BlocksMutation() const;
};

#endif // DROSERA_HPP