#include "UI/UIManager.hpp"

UIManager::UIManager()
    : currentPhase(GamePhase::MENU) {
}

void UIManager::Update(GamePhase phase) {
    currentPhase = phase;
    
    switch (phase) {
        case GamePhase::MENU:
            // Menu é atualizado separadamente
            break;
            
        case GamePhase::NIGHT_PHASE:
            plantMenu.Update();
            hackingMinigame.Update(GetFrameTime());
            break;
            
        default:
            break;
    }
    
    // Atualizar mensagens
    for (auto it = messages.begin(); it != messages.end();) {
        it->duration -= GetFrameTime();
        if (it->duration <= 0.0f) {
            it = messages.erase(it);
        } else {
            ++it;
        }
    }
}

void UIManager::Render(GamePhase phase) {
    switch (phase) {
        case GamePhase::MENU:
            menu.Render();
            break;
            
        case GamePhase::NIGHT_PHASE:
            // HUD é renderizado separadamente
            plantMenu.Render();
            hackingMinigame.Render();
            break;
            
        default:
            break;
    }
    
    RenderMessages();
}

void UIManager::ShowMessage(const std::string& message, float duration) {
    Message msg;
    msg.text = message;
    msg.duration = duration;
    msg.color = COLOR_TEXT;
    
    messages.push_back(msg);
}

void UIManager::RenderMessages() {
    int yOffset = 200;
    
    for (const auto& msg : messages) {
        // Fade out no final
        unsigned char alpha = 255;
        if (msg.duration < 1.0f) {
            alpha = (unsigned char)(255 * msg.duration);
        }
        
        Color msgColor = msg.color;
        msgColor.a = alpha;
        
        int textWidth = MeasureText(msg.text.c_str(), 24);
        DrawText(msg.text.c_str(), 
                SCREEN_WIDTH/2 - textWidth/2, 
                yOffset, 
                24, 
                msgColor);
        
        yOffset += 35;
    }
}