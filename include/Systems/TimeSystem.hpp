#ifndef TIMESYSTEM_HPP
#define TIMESYSTEM_HPP

#include "Utils/Constants.hpp"

class TimeSystem {
private:
    float nightTimer;
    float totalGameTime;
    bool isPaused;
    
    const float NIGHT_DURATION_SECONDS = 360.0f;  // 6 minutos

public:
    TimeSystem();
    
    void Update(float deltaTime);
    void Reset();
    void ResetNight();
    
    // Controle
    void Pause() { isPaused = true; }
    void Resume() { isPaused = false; }
    void TogglePause() { isPaused = !isPaused; }
    
    // Getters
    float GetNightTimeLeft() const { return nightTimer; }
    float GetNightTimeElapsed() const { return NIGHT_DURATION_SECONDS - nightTimer; }
    float GetNightProgress() const { return 1.0f - (nightTimer / NIGHT_DURATION_SECONDS); }
    float GetTotalGameTime() const { return totalGameTime; }
    bool IsPaused() const { return isPaused; }
    bool IsNightOver() const { return nightTimer <= 0.0f; }
    
    // Formatação
    void GetFormattedTime(int& minutes, int& seconds) const;
    float GetTimeInSeconds() const { return nightTimer; }
};

#endif // TIMESYSTEM_HPP