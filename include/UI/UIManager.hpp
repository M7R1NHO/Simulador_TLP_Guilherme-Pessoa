#ifndef UIMANAGER_HPP
#define UIMANAGER_HPP

#include "UI/Menu.hpp"
#include "UI/HUD.hpp"
#include "UI/PlantMenu.hpp"
#include "UI/HackingMinigame.hpp"
#include "Utils/Constants.hpp"

class UIManager {
private:
    Menu menu;
    HUD hud;
    PlantMenu plantMenu;
    HackingMinigame hackingMinigame;
    
    GamePhase currentPhase;

public:
    UIManager();
    
    void Update(GamePhase phase);
    void Render(GamePhase phase);
    
    // Menu
    MenuAction HandleMenuInput() { return menu.HandleInput(); }
    void UpdateMenu(bool hasSave) { menu.Update(hasSave); }
    void RenderMenu() { menu.Render(); }
    
    // HUD
    void RenderHUD(int day, int patient, float timeLeft, int step, int total) {
        hud.Render(day, patient, timeLeft, step, total);
    }
    
    void RenderRecipeProgress(int step, int total, const std::string& current) {
        hud.RenderRecipeProgress(step, total, current);
    }
    
    void RenderWarnings(bool toxin, float toxinTime, bool mask, float maskTime, 
                       bool uv, float uvProgress) {
        hud.RenderWarnings(toxin, toxinTime, mask, maskTime, uv, uvProgress);
    }
    
    // Plant Menu
    PlantMenu& GetPlantMenu() { return plantMenu; }
    
    // Hacking
    HackingMinigame& GetHackingMinigame() { return hackingMinigame; }
    
    // Mensagens
    void ShowMessage(const std::string& message, float duration);
    void RenderMessages();

private:
    // Sistema de mensagens
    struct Message {
        std::string text;
        float duration;
        Color color;
    };
    std::vector<Message> messages;
};

#endif // UIMANAGER_HPP