#ifndef PAPOULA_HPP
#define PAPOULA_HPP

#include "Entities/Planta.hpp"

class Papoula : public Planta {
private:
    bool isProducingToxin;

public:
    Papoula(Vector2 pos);
    
    void Update(float deltaTime) override;
    void Render() override;
    void ProcessAction(PlantAction action) override;
    
    void OnMutate() override;
    void OnDemutate() override;
    
    // Toxina
    bool IsProducingToxin() const { return isProducingToxin; }
    void ApplyToxinEffects(std::vector<std::unique_ptr<class Experimento>>& experiments, float deltaTime);
    bool ShouldWarnPlayer() const;
};

#endif // PAPOULA_HPP