#ifndef EXPERIMENTO_HPP
#define EXPERIMENTO_HPP

#include "raylib.h"
#include <string>

class Experimento {
private:
    int id;
    int stress;
    int irritation;
    int temperature;
    bool isSedated;
    Vector2 position;
    
    std::string name;
    std::string description;

public:
    Experimento(int experimentId, Vector2 pos);
    
    void Update(float deltaTime);
    void Render();
    
    // Ações
    void AdjustTemperature(bool makeHot);
    void ToggleTemperature();  // Para o Superior inverter
    void InjectAntiIrritation();
    void ApplySedative();
    
    // Efeitos de toxinas
    void ApplyNicotianaToxin(float deltaTime);
    void ApplyPapoulaToxin(float deltaTime);
    
    // Getters
    int GetStress() const { return stress; }
    int GetIrritation() const { return irritation; }
    bool CanCollectDNA() const;
    bool IsSedated() const { return isSedated; }
    
    // Setters
    void ModifyStress(int amount);
    void ModifyIrritation(int amount);
    
    std::string GetInfo() const;
};

#endif // EXPERIMENTO_HPP