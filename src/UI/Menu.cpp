#include "UI/Menu.hpp"
#include "Utils/Constants.hpp"

Menu::Menu()
    : saveExists(false),
      showingCredits(false),
      creditsScroll(0.0f) {
    
    CreateButtons();
}

void Menu::CreateButtons() {
    buttons.clear();
    
    int buttonWidth = 300;
    int buttonHeight = 60;
    int startY = 350;
    int spacing = 20;
    
    // Botão Começar/Retomar
    Button startButton({
        (float)(SCREEN_WIDTH/2 - buttonWidth/2),
        (float)startY,
        (float)buttonWidth,
        (float)buttonHeight
    }, "COMECAR");
    buttons.push_back(startButton);
    
    // Botão Créditos
    Button creditsButton({
        (float)(SCREEN_WIDTH/2 - buttonWidth/2),
        (float)(startY + buttonHeight + spacing),
        (float)buttonWidth,
        (float)buttonHeight
    }, "CREDITOS");
    buttons.push_back(creditsButton);
    
    // Botão Sair
    Button exitButton({
        (float)(SCREEN_WIDTH/2 - buttonWidth/2),
        (float)(startY + (buttonHeight + spacing) * 2),
        (float)buttonWidth,
        (float)buttonHeight
    }, "SAIR");
    buttons.push_back(exitButton);
}

void Menu::Update(bool hasSaveFile) {
    saveExists = hasSaveFile;
    
    // Atualizar texto do primeiro botão
    if (saveExists) {
        buttons[0].SetText("RETOMAR JOGO");
    } else {
        buttons[0].SetText("COMECAR");
    }
    
    // Atualizar botões
    for (auto& button : buttons) {
        button.Update();
    }
    
    // Scroll dos créditos
    if (showingCredits) {
        creditsScroll += 0.5f;
    }
}

void Menu::Render() {
    if (showingCredits) {
        RenderCredits();
        return;
    }
    
    // Fundo
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_BACKGROUND);
    
    // Título
    const char* title = "MUTANT FACILITY";
    int titleWidth = MeasureText(title, 70);
    DrawText(title, SCREEN_WIDTH/2 - titleWidth/2, 150, 70, COLOR_TEXT);
    
    // Subtítulo
    const char* subtitle = "Survival Game";
    int subtitleWidth = MeasureText(subtitle, 30);
    DrawText(subtitle, SCREEN_WIDTH/2 - subtitleWidth/2, 230, 30, GRAY);
    
    // Botões
    for (auto& button : buttons) {
        button.Render();
    }
    
    // Instruções
    const char* instructions = "Use o mouse para navegar";
    int instrWidth = MeasureText(instructions, 18);
    DrawText(instructions, SCREEN_WIDTH/2 - instrWidth/2, SCREEN_HEIGHT - 50, 18, GRAY);
}

void Menu::RenderCredits() {
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_BACKGROUND);
    
    int startY = SCREEN_HEIGHT - (int)creditsScroll;
    int lineHeight = 40;
    int currentY = startY;
    
    // Título
    const char* title = "CREDITOS";
    int titleWidth = MeasureText(title, 50);
    DrawText(title, SCREEN_WIDTH/2 - titleWidth/2, currentY, 50, COLOR_TEXT);
    currentY += 100;
    
    // Desenvolvedor
    DrawText("Desenvolvido por:", SCREEN_WIDTH/2 - 150, currentY, 24, COLOR_WARNING);
    currentY += lineHeight;
    DrawText("Guilherme", SCREEN_WIDTH/2 - 100, currentY, 28, COLOR_TEXT);
    currentY += lineHeight * 2;
    
    // Engine
    DrawText("Engine Grafica:", SCREEN_WIDTH/2 - 150, currentY, 24, COLOR_WARNING);
    currentY += lineHeight;
    DrawText("Raylib 5.0", SCREEN_WIDTH/2 - 100, currentY, 28, COLOR_TEXT);
    currentY += lineHeight * 2;
    
    // Linguagem
    DrawText("Linguagem:", SCREEN_WIDTH/2 - 150, currentY, 24, COLOR_WARNING);
    currentY += lineHeight;
    DrawText("C++17", SCREEN_WIDTH/2 - 100, currentY, 28, COLOR_TEXT);
    currentY += lineHeight * 2;
    
    // Projeto
    DrawText("Projeto Academico:", SCREEN_WIDTH/2 - 150, currentY, 24, COLOR_WARNING);
    currentY += lineHeight;
    DrawText("Programacao C/C++ Avancada", SCREEN_WIDTH/2 - 200, currentY, 22, COLOR_TEXT);
    currentY += lineHeight * 2;
    
    // Ano
    DrawText("2024", SCREEN_WIDTH/2 - 50, currentY, 28, GRAY);
    currentY += lineHeight * 3;
    
    // Agradecimentos
    DrawText("Obrigado por jogar!", SCREEN_WIDTH/2 - 150, currentY, 26, COLOR_SUCCESS);
    
    // Instrução para voltar
    if (creditsScroll > 100) {
        DrawText("Pressione ESC para voltar", SCREEN_WIDTH/2 - 180, 20, 20, COLOR_WARNING);
    }
}

MenuAction Menu::HandleInput() {
    if (showingCredits) {
        if (IsKeyPressed(KEY_ESCAPE)) {
            HideCredits();
        }
        return MenuAction::NONE;
    }
    
    // Verificar cliques nos botões
    if (buttons[0].IsClicked()) {
        return saveExists ? MenuAction::RESUME_GAME : MenuAction::NEW_GAME;
    }
    
    if (buttons[1].IsClicked()) {
        ShowCredits();
        return MenuAction::CREDITS;
    }
    
    if (buttons[2].IsClicked()) {
        return MenuAction::EXIT;
    }
    
    // Teclas de atalho
    if (IsKeyPressed(KEY_ENTER)) {
        return saveExists ? MenuAction::RESUME_GAME : MenuAction::NEW_GAME;
    }
    
    if (IsKeyPressed(KEY_ESCAPE)) {
        return MenuAction::EXIT;
    }
    
    if (IsKeyPressed(KEY_C)) {
        ShowCredits();
        return MenuAction::CREDITS;
    }
    
    return MenuAction::NONE;
}