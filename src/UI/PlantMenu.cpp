#include "UI/PlantMenu.hpp"
#include "Entities/Planta.hpp"
#include "Entities/Dionaea.hpp"

PlantMenu::PlantMenu()
    : selectedPlant(nullptr),
      isOpen(false),
      menuPosition({0, 0}) {
}

void PlantMenu::Open(Planta* plant, Vector2 clickPosition) {
    if (!plant) return;
    
    selectedPlant = plant;
    isOpen = true;
    
    // Posicionar menu próximo ao clique, mas dentro da tela
    menuPosition = clickPosition;
    
    // Ajustar se sair da tela
    if (menuPosition.x + MENU_WIDTH > SCREEN_WIDTH) {
        menuPosition.x = SCREEN_WIDTH - MENU_WIDTH - 10;
    }
    if (menuPosition.y + MENU_HEIGHT > SCREEN_HEIGHT) {
        menuPosition.y = SCREEN_HEIGHT - MENU_HEIGHT - 10;
    }
    
    CreateButtons();
}

void PlantMenu::Close() {
    isOpen = false;
    selectedPlant = nullptr;
    buttons.clear();
}

void PlantMenu::CreateButtons() {
    buttons.clear();
    
    float yOffset = menuPosition.y + 40;  // Espaço para título
    float xPos = menuPosition.x + 10;
    float buttonWidth = MENU_WIDTH - 20;
    
    // Botão Mutar
    buttons.push_back({
        {xPos, yOffset, buttonWidth, (float)BUTTON_HEIGHT},
        GetActionName(PlantAction::MUTATE),
        PlantAction::MUTATE,
        selectedPlant->CanMutate(),
        false
    });
    yOffset += BUTTON_HEIGHT + BUTTON_SPACING;
    
    // Botão Adubar
    buttons.push_back({
        {xPos, yOffset, buttonWidth, (float)BUTTON_HEIGHT},
        GetActionName(PlantAction::FERTILIZE),
        PlantAction::FERTILIZE,
        selectedPlant->CanFertilize(),
        false
    });
    yOffset += BUTTON_HEIGHT + BUTTON_SPACING;
    
    // Botão Coletar
    buttons.push_back({
        {xPos, yOffset, buttonWidth, (float)BUTTON_HEIGHT},
        GetActionName(PlantAction::COLLECT),
        PlantAction::COLLECT,
        selectedPlant->CanCollect(),
        false
    });
    yOffset += BUTTON_HEIGHT + BUTTON_SPACING;
    
    // Botão Regar
    buttons.push_back({
        {xPos, yOffset, buttonWidth, (float)BUTTON_HEIGHT},
        GetActionName(PlantAction::WATER),
        PlantAction::WATER,
        selectedPlant->IsAlive(),
        false
    });
    yOffset += BUTTON_HEIGHT + BUTTON_SPACING;
    
    // Botão Replantar (só se morta)
    if (!selectedPlant->IsAlive()) {
        buttons.push_back({
            {xPos, yOffset, buttonWidth, (float)BUTTON_HEIGHT},
            GetActionName(PlantAction::REPLANT),
            PlantAction::REPLANT,
            true,
            false
        });
        yOffset += BUTTON_HEIGHT + BUTTON_SPACING;
    }
    
    // Botão Alimentar (só para Dionaea)
    Dionaea* dionaea = dynamic_cast<Dionaea*>(selectedPlant);
    if (dionaea) {
        buttons.push_back({
            {xPos, yOffset, buttonWidth, (float)BUTTON_HEIGHT},
            GetActionName(PlantAction::FEED),
            PlantAction::FEED,
            dionaea->CanBeFed(),
            false
        });
    }
}

void PlantMenu::Update() {
    if (!isOpen) return;
    
    UpdateButtonStates();
}

void PlantMenu::UpdateButtonStates() {
    Vector2 mousePos = GetMousePosition();
    
    for (auto& button : buttons) {
        button.isHovered = button.isEnabled && 
                          CheckCollisionPointRec(mousePos, button.bounds);
    }
}

PlantAction PlantMenu::HandleClick(Vector2 mousePos) {
    if (!isOpen) return PlantAction::COLLECT;  // Valor padrão
    
    for (const auto& button : buttons) {
        if (button.isEnabled && CheckCollisionPointRec(mousePos, button.bounds)) {
            return button.action;
        }
    }
    
    // Clicou fora do menu? Fechar
    Rectangle menuBounds = {
        menuPosition.x, 
        menuPosition.y, 
        (float)MENU_WIDTH, 
        (float)MENU_HEIGHT
    };
    
    if (!CheckCollisionPointRec(mousePos, menuBounds)) {
        Close();
    }
    
    return PlantAction::COLLECT;  // Valor padrão
}

void PlantMenu::Render() {
    if (!isOpen || !selectedPlant) return;
    
    // Fundo do menu
    DrawRectangle(menuPosition.x, menuPosition.y, MENU_WIDTH, MENU_HEIGHT, 
                 (Color){30, 30, 40, 240});
    DrawRectangleLines(menuPosition.x, menuPosition.y, MENU_WIDTH, MENU_HEIGHT, 
                      COLOR_TEXT);
    
    // Título
    std::string title = "PLANTA";
    int titleWidth = MeasureText(title.c_str(), 20);
    DrawText(title.c_str(), 
             menuPosition.x + (MENU_WIDTH - titleWidth) / 2, 
             menuPosition.y + 10, 
             20, 
             COLOR_TEXT);
    
    // Estado da planta
    std::string stateText = selectedPlant->GetIngredientName();
    int stateWidth = MeasureText(stateText.c_str(), 14);
    DrawText(stateText.c_str(), 
             menuPosition.x + (MENU_WIDTH - stateWidth) / 2, 
             menuPosition.y + 35, 
             14, 
             COLOR_WARNING);
    
    // Botões
    for (const auto& button : buttons) {
        RenderButton(button);
    }
}

void PlantMenu::RenderButton(const MenuButton& button) {
    Color bgColor;
    Color textColor;
    
    if (!button.isEnabled) {
        bgColor = DARKGRAY;
        textColor = GRAY;
    } else if (button.isHovered) {
        bgColor = GetActionColor(button.action);
        textColor = BLACK;
    } else {
        bgColor = COLOR_UI;
        textColor = COLOR_TEXT;
    }
    
    DrawRectangleRec(button.bounds, bgColor);
    DrawRectangleLinesEx(button.bounds, 2, textColor);
    
    // Centralizar texto
    int textWidth = MeasureText(button.text.c_str(), 18);
    float textX = button.bounds.x + (button.bounds.width - textWidth) / 2;
    float textY = button.bounds.y + (button.bounds.height - 18) / 2;
    
    DrawText(button.text.c_str(), textX, textY, 18, textColor);
}

std::string PlantMenu::GetActionName(PlantAction action) const {
    switch (action) {
        case PlantAction::MUTATE: return "MUTAR";
        case PlantAction::FERTILIZE: return "ADUBAR";
        case PlantAction::COLLECT: return "COLETAR";
        case PlantAction::WATER: return "REGAR";
        case PlantAction::REPLANT: return "REPLANTAR";
        case PlantAction::FEED: return "ALIMENTAR";
        default: return "?";
    }
}

Color PlantMenu::GetActionColor(PlantAction action) const {
    switch (action) {
        case PlantAction::MUTATE: return (Color){200, 100, 200, 255};  // Roxo
        case PlantAction::FERTILIZE: return (Color){100, 200, 100, 255};  // Verde
        case PlantAction::COLLECT: return COLOR_WARNING;  // Amarelo
        case PlantAction::WATER: return BLUE;
        case PlantAction::REPLANT: return ORANGE;
        case PlantAction::FEED: return RED;
        default: return GRAY;
    }
}