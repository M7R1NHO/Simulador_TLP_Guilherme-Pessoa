#include "UI/HUD.hpp"
#include "Utils/Constants.hpp"

HUD::HUD() {
}

void HUD::Render(int currentDay, int selectedPatient, float timeLeft, 
                 int recipeStep, int totalSteps) {
    // Painel superior
    DrawRectangle(0, 0, SCREEN_WIDTH, 60, COLOR_UI);
    
    RenderDayInfo(currentDay, TOTAL_DAYS);
    RenderTimer(timeLeft);
    
    // Paciente
    std::string patientText = "Paciente: " + std::to_string(selectedPatient);
    DrawText(patientText.c_str(), 300, 20, 24, COLOR_TEXT);
}

void HUD::RenderDayInfo(int day, int totalDays) {
    std::string dayText = "Dia " + std::to_string(day) + "/" + std::to_string(totalDays);
    DrawText(dayText.c_str(), 20, 20, 24, COLOR_TEXT);
}

void HUD::RenderTimer(float timeLeft) {
    int minutes = (int)(timeLeft / 60.0f);
    int seconds = (int)timeLeft % 60;
    
    char timeStr[32];
    sprintf(timeStr, "Tempo: %02d:%02d", minutes, seconds);
    
    Color timerColor = GetTimerColor(timeLeft);
    DrawText(timeStr, SCREEN_WIDTH - 200, 20, 24, timerColor);
}

void HUD::RenderRecipeProgress(int currentStep, int totalSteps, 
                                const std::string& currentIngredient) {
    // Painel de receita (lado direito)
    int panelX = SCREEN_WIDTH - 320;
    int panelY = 80;
    int panelWidth = 300;
    int panelHeight = 200;
    
    DrawRectangle(panelX, panelY, panelWidth, panelHeight, COLOR_UI);
    DrawRectangleLines(panelX, panelY, panelWidth, panelHeight, COLOR_TEXT);
    
    DrawText("RECEITA", panelX + 10, panelY + 10, 20, COLOR_TEXT);
    
    // Progresso
    std::string progressText = std::to_string(currentStep) + "/" + std::to_string(totalSteps);
    DrawText(progressText.c_str(), panelX + 10, panelY + 40, 18, COLOR_WARNING);
    
    // Barra de progresso
    float progress = (float)currentStep / (float)totalSteps;
    Rectangle progressBar = {(float)(panelX + 10), (float)(panelY + 70), 280, 20};
    DrawProgressBar(progressBar, progress, COLOR_SUCCESS);
    
    // Ingrediente atual
    if (currentStep < totalSteps) {
        DrawText("Proximo:", panelX + 10, panelY + 100, 16, GRAY);
        DrawText(currentIngredient.c_str(), panelX + 10, panelY + 120, 14, COLOR_TEXT);
    } else {
        DrawText("RECEITA COMPLETA!", panelX + 10, panelY + 100, 18, COLOR_SUCCESS);
    }
}

void HUD::RenderWarnings(bool toxinWarning, float toxinTime, 
                         bool maskActive, float maskTime,
                         bool uvActive, float uvProgress) {
    int warningY = 100;
    
    // Aviso de toxina
    if (toxinWarning) {
        DrawRectangle(SCREEN_WIDTH/2 - 200, warningY, 400, 60, COLOR_DANGER);
        DrawText("⚠ INALANDO TOXINA!", SCREEN_WIDTH/2 - 140, warningY + 10, 24, WHITE);
        
        char timeText[32];
        sprintf(timeText, "Tempo: %.1fs", toxinTime);
        DrawText(timeText, SCREEN_WIDTH/2 - 80, warningY + 35, 18, WHITE);
        
        warningY += 70;
    }
    
    // Status da máscara
    if (maskActive) {
        DrawRectangle(SCREEN_WIDTH - 220, warningY, 200, 40, (Color){50, 100, 200, 200});
        
        char maskText[32];
        sprintf(maskText, "Mascara: %.0fs", maskTime);
        DrawText(maskText, SCREEN_WIDTH - 210, warningY + 10, 18, WHITE);
        
        warningY += 50;
    }
    
    // Status UV
    if (uvActive) {
        DrawRectangle(SCREEN_WIDTH - 220, warningY, 200, 50, (Color){200, 100, 200, 200});
        DrawText("Luz UV", SCREEN_WIDTH - 210, warningY + 5, 18, WHITE);
        
        Rectangle uvBar = {(float)(SCREEN_WIDTH - 210), (float)(warningY + 30), 180, 15};
        DrawProgressBar(uvBar, uvProgress, PURPLE);
    }
}

void HUD::RenderExperimentInfo(int expId, int stress, int irritation, bool canCollectDNA) {
    // Mini painel de info do experimento (quando focado)
    int panelX = 20;
    int panelY = SCREEN_HEIGHT - 250;
    int panelWidth = 250;
    int panelHeight = 150;
    
    DrawRectangle(panelX, panelY, panelWidth, panelHeight, COLOR_UI);
    DrawRectangleLines(panelX, panelY, panelWidth, panelHeight, COLOR_TEXT);
    
    std::string title = "Experimento " + std::to_string(expId);
    DrawText(title.c_str(), panelX + 10, panelY + 10, 18, COLOR_TEXT);
    
    // Stress
    std::string stressText = "Stress: " + std::to_string(stress) + "%";
    DrawText(stressText.c_str(), panelX + 10, panelY + 40, 16, COLOR_TEXT);
    
    Rectangle stressBar = {(float)(panelX + 10), (float)(panelY + 60), 230, 15};
    DrawProgressBar(stressBar, stress / 100.0f, BLUE);
    
    // Irritação
    std::string irritText = "Irritacao: " + std::to_string(irritation) + "%";
    DrawText(irritText.c_str(), panelX + 10, panelY + 85, 16, COLOR_TEXT);
    
    Rectangle irritBar = {(float)(panelX + 10), (float)(panelY + 105), 230, 15};
    DrawProgressBar(irritBar, irritation / 100.0f, RED);
    
    // DNA
    if (canCollectDNA) {
        DrawText("★ DNA PRONTO!", panelX + 10, panelY + 125, 16, COLOR_SUCCESS);
    }
}

Color HUD::GetTimerColor(float timeLeft) const {
    if (timeLeft < 60.0f) return COLOR_DANGER;
    if (timeLeft < 180.0f) return COLOR_WARNING;
    return COLOR_TEXT;
}

void HUD::DrawProgressBar(Rectangle bounds, float progress, Color fillColor) {
    // Fundo
    DrawRectangleRec(bounds, DARKGRAY);
    
    // Preenchimento
    Rectangle fill = bounds;
    fill.width = bounds.width * progress;
    DrawRectangleRec(fill, fillColor);
    
    // Borda
    DrawRectangleLinesEx(bounds, 2, COLOR_TEXT);
}