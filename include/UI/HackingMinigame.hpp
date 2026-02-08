#ifndef HACKINGMINIGAME_HPP
#define HACKINGMINIGAME_HPP

#include "raylib.h"

class HackingMinigame {
private:
    bool active;
    float progress;  // 0.0 a 1.0
    bool completed;
    
    const float HACK_SPEED = 0.15f;  // 15% por segundo (total ~6.7s)
    
    Rectangle barBounds;
    Rectangle fillBounds;

public:
    HackingMinigame();
    
    void Start();
    void Stop();
    void Update(float deltaTime);
    void Render();
    
    // Getters
    bool IsActive() const { return active; }
    bool IsCompleted() const { return completed; }
    float GetProgress() const { return progress; }
    
    // Reset
    void Reset();
};

#endif // HACKINGMINIGAME_HPP