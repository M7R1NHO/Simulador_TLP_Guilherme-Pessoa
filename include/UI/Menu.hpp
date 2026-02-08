#ifndef MENU_HPP
#define MENU_HPP

#include "UI/Button.hpp"
#include <vector>

enum class MenuAction {
    NONE,
    NEW_GAME,
    RESUME_GAME,
    CREDITS,
    EXIT
};

class Menu {
private:
    std::vector<Button> buttons;
    bool saveExists;
    
    // Créditos
    bool showingCredits;
    float creditsScroll;

public:
    Menu();
    
    void Update(bool hasSaveFile);
    void Render();
    void RenderCredits();
    
    MenuAction HandleInput();
    
    // Controle de créditos
    void ShowCredits() { showingCredits = true; creditsScroll = 0; }
    void HideCredits() { showingCredits = false; }
    bool IsShowingCredits() const { return showingCredits; }

private:
    void CreateButtons();
};

#endif // MENU_HPP