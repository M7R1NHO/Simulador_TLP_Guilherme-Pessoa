#include "Systems/MapSystem.hpp"
#include <iostream>

MapSystem::MapSystem()
    : currentLocation(MapLocation::CORREDOR),
      currentPhase(DayPhase::DUSK),
      transitioning(false),
      transitionTimer(0.0f) {
    
    InitializeLocations();
    InitializeButtons();
}

void MapSystem::InitializeLocations() {
    // Posições de câmera para cada local
    locationPositions[MapLocation::CORREDOR] = {640, 360};
    locationPositions[MapLocation::SALA] = {640, 360};
    locationPositions[MapLocation::PACIENTES] = {640, 200};
    locationPositions[MapLocation::JARDIM] = {400, 400};
    locationPositions[MapLocation::JAULA_1] = {900, 200};
    locationPositions[MapLocation::JAULA_2] = {1100, 200};
    locationPositions[MapLocation::JAULA_3] = {900, 500};
    locationPositions[MapLocation::JAULA_4] = {1100, 500};
    locationPositions[MapLocation::ESTOQUE] = {200, 600};
}

void MapSystem::InitializeButtons() {
    // Criar botões de navegação (canto superior)
    int buttonWidth = 120;
    int buttonHeight = 35;
    int startX = 20;
    int startY = 80;
    int spacing = 10;
    
    navigationButtons = {
        {{(float)startX, (float)startY, (float)buttonWidth, (float)buttonHeight}, 
         MapLocation::SALA, "Sala", true, false},
        
        {{(float)(startX + (buttonWidth + spacing) * 1), (float)startY, (float)buttonWidth, (float)buttonHeight}, 
         MapLocation::JARDIM, "Jardim", true, false},
        
        {{(float)(startX + (buttonWidth + spacing) * 2), (float)startY, (float)buttonWidth, (float)buttonHeight}, 
         MapLocation::ESTOQUE, "Estoque", true, false},
        
        {{(float)startX, (float)(startY + buttonHeight + spacing), (float)buttonWidth, (float)buttonHeight}, 
         MapLocation::JAULA_1, "Jaula 1", true, false},
        
        {{(float)(startX + (buttonWidth + spacing) * 1), (float)(startY + buttonHeight + spacing), (float)buttonWidth, (float)buttonHeight}, 
         MapLocation::JAULA_2, "Jaula 2", true, false},
        
        {{(float)(startX + (buttonWidth + spacing) * 2), (float)(startY + buttonHeight + spacing), (float)buttonWidth, (float)buttonHeight}, 
         MapLocation::JAULA_3, "Jaula 3", true, false},
        
        {{(float)(startX + (buttonWidth + spacing) * 3), (float)(startY + buttonHeight + spacing), (float)buttonWidth, (float)buttonHeight}, 
         MapLocation::JAULA_4, "Jaula 4", true, false},
    };
}

void MapSystem::Update(float deltaTime, DayPhase phase) {
    currentPhase = phase;
    
    // Atualizar estados dos botões baseado na fase
    UpdateButtonStates(phase);
    
    // Atualizar transição
    if (transitioning) {
        transitionTimer -= deltaTime;
        if (transitionTimer <= 0.0f) {
            transitioning = false;
        }
    }
}

void MapSystem::UpdateButtonStates(DayPhase phase) {
    for (auto& button : navigationButtons) {
        button.isAvailable = CanAccessLocation(button.location, phase);
        
        // Verificar hover
        Vector2 mousePos = GetMousePosition();
        button.isHovered = CheckCollisionPointRec(mousePos, button.bounds) && button.isAvailable;
    }
}

bool MapSystem::CanAccessLocation(MapLocation loc, DayPhase phase) const {
    switch (loc) {
        case MapLocation::CORREDOR:
            return phase == DayPhase::DUSK;
            
        case MapLocation::PACIENTES:
            return phase == DayPhase::DUSK;
            
        case MapLocation::SALA:
            return phase == DayPhase::NIGHT;
            
        case MapLocation::JARDIM:
            return phase == DayPhase::NIGHT;
            
        case MapLocation::JAULA_1:
        case MapLocation::JAULA_2:
        case MapLocation::JAULA_3:
        case MapLocation::JAULA_4:
        case MapLocation::ESTOQUE:
            return true;  // Sempre disponíveis
            
        default:
            return false;
    }
}

void MapSystem::ChangeLocation(MapLocation newLocation) {
    if (currentLocation == newLocation) return;
    
    if (CanAccessLocation(newLocation, currentPhase)) {
        currentLocation = newLocation;
        transitioning = true;
        transitionTimer = TRANSITION_DURATION;
        
        std::cout << "[MAPA] Movendo para: " << GetLocationName(newLocation) << std::endl;
    } else {
        std::cout << "[MAPA] Local nao acessivel nesta fase!" << std::endl;
    }
}

bool MapSystem::HandleLocationClick(Vector2 mousePos) {
    if (transitioning) return false;
    
    for (const auto& button : navigationButtons) {
        if (button.isAvailable && CheckCollisionPointRec(mousePos, button.bounds)) {
            ChangeLocation(button.location);
            return true;
        }
    }
    
    return false;
}

void MapSystem::Render() {
    RenderNavigationButtons();
    RenderCurrentLocation();
}

void MapSystem::RenderNavigationButtons() {
    for (const auto& button : navigationButtons) {
        Color bgColor;
        Color textColor;
        
        if (!button.isAvailable) {
            bgColor = DARKGRAY;
            textColor = GRAY;
        } else if (button.location == currentLocation) {
            bgColor = COLOR_SUCCESS;
            textColor = BLACK;
        } else if (button.isHovered) {
            bgColor = COLOR_WARNING;
            textColor = BLACK;
        } else {
            bgColor = COLOR_UI;
            textColor = COLOR_TEXT;
        }
        
        DrawRectangleRec(button.bounds, bgColor);
        DrawRectangleLinesEx(button.bounds, 2, textColor);
        
        // Centralizar texto
        int textWidth = MeasureText(button.name.c_str(), 16);
        float textX = button.bounds.x + (button.bounds.width - textWidth) / 2;
        float textY = button.bounds.y + (button.bounds.height - 16) / 2;
        
        DrawText(button.name.c_str(), textX, textY, 16, textColor);
    }
}

void MapSystem::RenderCurrentLocation() {
    // Mostrar nome do local atual
    std::string locationText = "Local: " + GetLocationName(currentLocation);
    DrawText(locationText.c_str(), 20, 50, 20, COLOR_TEXT);
    
    // Efeito de fade durante transição
    if (transitioning) {
        float alpha = (transitionTimer / TRANSITION_DURATION) * 255;
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 
                     (Color){0, 0, 0, (unsigned char)alpha});
    }
}

Vector2 MapSystem::GetLocationPosition(MapLocation loc) const {
    auto it = locationPositions.find(loc);
    if (it != locationPositions.end()) {
        return it->second;
    }
    return {640, 360};  // Default center
}

void MapSystem::SetPhase(DayPhase phase) {
    currentPhase = phase;
    
    // Mudar local inicial baseado na fase
    if (phase == DayPhase::DUSK) {
        currentLocation = MapLocation::CORREDOR;
    } else {
        currentLocation = MapLocation::SALA;
    }
}

std::string MapSystem::GetLocationName(MapLocation loc) const {
    switch (loc) {
        case MapLocation::CORREDOR: return "Corredor";
        case MapLocation::SALA: return "Sala";
        case MapLocation::PACIENTES: return "Pacientes";
        case MapLocation::JARDIM: return "Jardim";
        case MapLocation::JAULA_1: return "Jaula 1";
        case MapLocation::JAULA_2: return "Jaula 2";
        case MapLocation::JAULA_3: return "Jaula 3";
        case MapLocation::JAULA_4: return "Jaula 4";
        case MapLocation::ESTOQUE: return "Estoque";
        default: return "Desconhecido";
    }
}