#ifndef HUD_HPP
#define HUD_HPP

#include "raylib.h"
#include <string>

class HUD {
public:
    HUD();
    
    void Render(int currentDay, int selectedPatient, float timeLeft, 
                int recipeStep, int totalSteps);
    
    void RenderDayInfo(int day, int totalDays);
    void RenderTimer(float timeLeft);
    void RenderRecipeProgress(int currentStep, int totalSteps, 
                              const std::string& currentIngredient);
    void RenderWarnings(bool toxinWarning, float toxinTime, 
                       bool maskActive, float maskTime,
                       bool uvActive, float uvProgress);
    void RenderExperimentInfo(int expId, int stress, int irritation, bool canCollectDNA);
    
private:
    Color GetTimerColor(float timeLeft) const;
    void DrawProgressBar(Rectangle bounds, float progress, Color fillColor);
};

#endif // HUD_HPP