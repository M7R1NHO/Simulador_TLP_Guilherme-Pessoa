#include "Entities/Experimento.hpp"
#include "Utils/Constants.hpp"
#include <sstream>

Experimento::Experimento(int experimentId, Vector2 pos) 
    : id(experimentId),
      stress(50),
      irritation(50),
      temperature(20),
      isSedated(false),
      position(pos) {
    
    name = "Experimento " + std::to_string(id);
    description = "Sujeito de teste biologico";
}

void Experimento::Update(float deltaTime) {
    if (isSedated) {
        if (stress > 0) stress -= deltaTime * 2;
        if (irritation > 0) irritation -= deltaTime * 2;
    } else {
        if (stress < 100) stress += deltaTime * 0.5f;
        if (irritation < 100) irritation += deltaTime * 0.3f;
    }
    
    if (stress < 0) stress = 0;
    if (stress > 100) stress = 100;
    if (irritation < 0) irritation = 0;
    if (irritation > 100) irritation = 100;
}

void Experimento::Render() {
    DrawRectangleLines(position.x - 60, position.y - 60, 120, 120, DARKGRAY);
    
    Color stateColor = GREEN;
    if (irritation > 50 || stress > 50) stateColor = YELLOW;
    if (irritation > 75 || stress > 75) stateColor = RED;
    
    DrawCircleV(position, 25, stateColor);
    DrawText(std::to_string(id).c_str(), position.x - 5, position.y - 8, 20, BLACK);
    
    // Stress
    float stressPercent = stress / 100.0f;
    DrawRectangle(position.x - 50, position.y + 40, 100, 8, DARKGRAY);
    DrawRectangle(position.x - 50, position.y + 40, 100 * stressPercent, 8, BLUE);
    DrawText("Stress", position.x - 50, position.y + 50, 10, COLOR_TEXT);
    
    // Irritação
    float irritPercent = irritation / 100.0f;
    DrawRectangle(position.x - 50, position.y + 60, 100, 8, DARKGRAY);
    DrawRectangle(position.x - 50, position.y + 60, 100 * irritPercent, 8, RED);
    DrawText("Irritacao", position.x - 50, position.y + 70, 10, COLOR_TEXT);
    
    if (isSedated) {
        DrawText("SEDADO", position.x - 30, position.y - 40, 12, COLOR_SUCCESS);
    }
}

void Experimento::AdjustTemperature(bool makeHot) {
    if (makeHot) {
        temperature += 5;
        if (id <= 2) stress -= 10;
        else stress += 10;
    } else {
        temperature -= 5;
        if (id > 2) stress -= 10;
        else stress += 10;
    }
}

void Experimento::ToggleTemperature() {
    // Inverter temperatura (para o Superior)
    if (id == 1 || id == 3) {
        // Prefere frio, forçar quente
        temperature = 30;  // Quente
        stress += 15;
    } else {
        // Prefere quente, forçar frio
        temperature = 10;  // Frio
        stress += 15;
    }
}

void Experimento::InjectAntiIrritation() {
    irritation = 0;
}

void Experimento::ApplySedative() {
    isSedated = true;
    stress = 0;
    irritation = 0;
}

void Experimento::ApplyNicotianaToxin(float deltaTime) {
    if (id <= 2) {
        stress -= deltaTime * 5;
    } else {
        irritation += deltaTime * 5;
    }
}

void Experimento::ApplyPapoulaToxin(float deltaTime) {
    if (id > 2) {
        stress -= deltaTime * 5;
    } else {
        irritation += deltaTime * 5;
    }
}

bool Experimento::CanCollectDNA() const {
    return irritation == 0 && stress >= 0 && stress <= 25;
}

void Experimento::ModifyStress(int amount) {
    stress += amount;
    if (stress < 0) stress = 0;
    if (stress > 100) stress = 100;
}

void Experimento::ModifyIrritation(int amount) {
    irritation += amount;
    if (irritation < 0) irritation = 0;
    if (irritation > 100) irritation = 100;
}

std::string Experimento::GetInfo() const {
    std::stringstream ss;
    ss << name << "\n";
    ss << "Stress: " << stress << "%\n";
    ss << "Irritacao: " << irritation << "%\n";
    ss << "Temperatura: " << temperature << "C\n";
    ss << "DNA coletavel: " << (CanCollectDNA() ? "Sim" : "Nao");
    return ss.str();
}