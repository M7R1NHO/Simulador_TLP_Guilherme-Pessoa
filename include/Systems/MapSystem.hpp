#ifndef MAPSYSTEM_HPP
#define MAPSYSTEM_HPP

#include "Utils/Constants.hpp"
#include "raylib.h"
#include <map>
#include <vector>
#include <string>

enum class MapLocation {
    CORREDOR,    // Apenas ANOITECER
    SALA,        // Apenas NOITE (hub)
    PACIENTES,   // Apenas ANOITECER
    JARDIM,      // Apenas NOITE
    JAULA_1,     // Ambos
    JAULA_2,     // Ambos
    JAULA_3,     // Ambos
    JAULA_4,     // Ambos
    ESTOQUE      // Ambos
};

struct LocationButton {
    Rectangle bounds;
    MapLocation location;
    std::string name;
    bool isAvailable;
    bool isHovered;
};

class MapSystem {
private:
    MapLocation currentLocation;
    DayPhase currentPhase;
    
    std::map<MapLocation, Vector2> locationPositions;
    std::vector<LocationButton> navigationButtons;
    
    bool transitioning;
    float transitionTimer;
    const float TRANSITION_DURATION = 0.5f;

public:
    MapSystem();
    
    void Update(float deltaTime, DayPhase phase);
    void Render();
    void RenderNavigationButtons();
    void RenderCurrentLocation();
    
    // Navegação
    bool CanAccessLocation(MapLocation loc, DayPhase phase) const;
    void ChangeLocation(MapLocation newLocation);
    bool HandleLocationClick(Vector2 mousePos);
    
    // Getters
    MapLocation GetCurrentLocation() const { return currentLocation; }
    Vector2 GetLocationPosition(MapLocation loc) const;
    bool IsTransitioning() const { return transitioning; }
    
    // Setters
    void SetPhase(DayPhase phase);
    void SetLocation(MapLocation loc) { currentLocation = loc; }
    
private:
    void InitializeLocations();
    void InitializeButtons();
    void UpdateButtonStates(DayPhase phase);
    std::string GetLocationName(MapLocation loc) const;
};

#endif // MAPSYSTEM_HPP