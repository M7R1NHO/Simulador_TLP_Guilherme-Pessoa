#ifndef FRND19_HPP
#define FRND19_HPP

#include "Entities/Planta.hpp"

class FRND19 : public Planta {
private:
    bool isBlockingSuperior;

public:
    FRND19(Vector2 pos);
    
    void Update(float deltaTime) override;
    void Render() override;
    void ProcessAction(PlantAction action) override;
    
    void OnMutate() override;
    void OnDemutate() override;
    
    // Bloqueio do Superior
    bool IsBlockingSuperior() const { return isBlockingSuperior; }
};

#endif // FRND19_HPP