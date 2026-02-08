#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "raylib.h"
#include <string>
#include <functional>

class Button {
private:
    Rectangle bounds;
    std::string text;
    Color normalColor;
    Color hoverColor;
    Color pressedColor;
    Color textColor;
    
    bool isHovered;
    bool isPressed;
    bool isEnabled;
    
    int fontSize;

public:
    Button();
    Button(Rectangle rect, const std::string& buttonText);
    
    void Update();
    void Render();
    
    // Interação
    bool IsClicked();
    bool IsHovering() const { return isHovered; }
    
    // Setters
    void SetPosition(float x, float y);
    void SetSize(float width, float height);
    void SetText(const std::string& newText) { text = newText; }
    void SetEnabled(bool enabled) { isEnabled = enabled; }
    void SetColors(Color normal, Color hover, Color pressed);
    void SetFontSize(int size) { fontSize = size; }
    
    // Getters
    Rectangle GetBounds() const { return bounds; }
    std::string GetText() const { return text; }
    bool IsEnabled() const { return isEnabled; }
};

#endif // BUTTON_HPP