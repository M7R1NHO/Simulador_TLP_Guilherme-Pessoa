#ifndef PLANTMENU_HPP
#define PLANTMENU_HPP

#include "raylib.h"
#include "Utils/Constants.hpp"
#include <vector>
#include <string>

class Planta;

struct MenuButton {
    Rectangle bounds;
    std::string text;
    PlantAction action;
    bool isEnabled;
    bool isHovered;
};

class PlantMenu {
private:
    Planta* selectedPlant;
    bool isOpen;
    Vector2 menuPosition;
    
    std::vector<MenuButton> buttons;
    
    const int MENU_WIDTH = 220;
    const int MENU_HEIGHT = 280;
    const int BUTTON_HEIGHT = 40;
    const int BUTTON_SPACING = 5;

public:
    PlantMenu();
    
    void Open(Planta* plant, Vector2 clickPosition);
    void Close();
    void Update();
    void Render();
    
    // Interação
    PlantAction HandleClick(Vector2 mousePos);
    
    // Getters
    bool IsOpen() const { return isOpen; }
    Planta* GetSelectedPlant() const { return selectedPlant; }
    
private:
    void CreateButtons();
    void UpdateButtonStates();
    void RenderButton(const MenuButton& button);
    std::string GetActionName(PlantAction action) const;
    Color GetActionColor(PlantAction action) const;
};

#endif // PLANTMENU_HPP