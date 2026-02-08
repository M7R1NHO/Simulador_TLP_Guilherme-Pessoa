#ifndef PACIENTE_HPP
#define PACIENTE_HPP

#include "raylib.h"
#include <string>
#include <vector>

class Paciente {
private:
    int id;
    std::string name;
    std::string description;
    std::vector<std::string> recipe;  // Lista de ingredientes necessários
    Vector2 position;
    bool isCured;

public:
    Paciente(int patientId, Vector2 pos);
    
    void Render();
    void RenderInfo();
    
    // Getters
    int GetId() const { return id; }
    std::string GetName() const { return name; }
    std::string GetDescription() const { return description; }
    std::vector<std::string> GetRecipe() const { return recipe; }
    bool IsCured() const { return isCured; }
    Vector2 GetPosition() const { return position; }
    
    // Setters
    void SetCured(bool cured) { isCured = cured; }
    
    // Verificar clique
    bool IsClicked(Vector2 mousePos) const;
    
private:
    void InitializePatientData();
};

#endif // PACIENTE_HPP