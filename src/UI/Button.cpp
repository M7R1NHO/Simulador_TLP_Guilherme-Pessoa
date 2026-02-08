#include "UI/Button.hpp"
#include "Utils/Constants.hpp"

Button::Button()
    : bounds({0, 0, 100, 40}),
      text("Button"),
      normalColor(COLOR_UI),
      hoverColor(COLOR_WARNING),
      pressedColor(COLOR_SUCCESS),
      textColor(COLOR_TEXT),
      isHovered(false),
      isPressed(false),
      isEnabled(true),
      fontSize(20) {
}

Button::Button(Rectangle rect, const std::string& buttonText)
    : bounds(rect),
      text(buttonText),
      normalColor(COLOR_UI),
      hoverColor(COLOR_WARNING),
      pressedColor(COLOR_SUCCESS),
      textColor(COLOR_TEXT),
      isHovered(false),
      isPressed(false),
      isEnabled(true),
      fontSize(20) {
}

void Button::Update() {
    if (!isEnabled) {
        isHovered = false;
        isPressed = false;
        return;
    }
    
    Vector2 mousePos = GetMousePosition();
    isHovered = CheckCollisionPointRec(mousePos, bounds);
    
    if (isHovered && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        isPressed = true;
    } else {
        isPressed = false;
    }
}

void Button::Render() {
    Color bgColor;
    
    if (!isEnabled) {
        bgColor = DARKGRAY;
    } else if (isPressed) {
        bgColor = pressedColor;
    } else if (isHovered) {
        bgColor = hoverColor;
    } else {
        bgColor = normalColor;
    }
    
    // Desenhar fundo
    DrawRectangleRec(bounds, bgColor);
    
    // Desenhar borda
    Color borderColor = isEnabled ? textColor : GRAY;
    DrawRectangleLinesEx(bounds, 2, borderColor);
    
    // Desenhar texto centralizado
    int textWidth = MeasureText(text.c_str(), fontSize);
    float textX = bounds.x + (bounds.width - textWidth) / 2;
    float textY = bounds.y + (bounds.height - fontSize) / 2;
    
    Color finalTextColor = isEnabled ? textColor : GRAY;
    DrawText(text.c_str(), textX, textY, fontSize, finalTextColor);
}

bool Button::IsClicked() {
    if (!isEnabled) return false;
    
    Vector2 mousePos = GetMousePosition();
    bool hovering = CheckCollisionPointRec(mousePos, bounds);
    
    return hovering && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

void Button::SetPosition(float x, float y) {
    bounds.x = x;
    bounds.y = y;
}

void Button::SetSize(float width, float height) {
    bounds.width = width;
    bounds.height = height;
}

void Button::SetColors(Color normal, Color hover, Color pressed) {
    normalColor = normal;
    hoverColor = hover;
    pressedColor = pressed;
}