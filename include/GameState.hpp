#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "Utils/Constants.hpp"

class GameState {
private:
    GamePhase currentPhase;
    DayPhase dayPhase;
    int currentDay;
    int selectedPatient;
    bool gameWon;
    bool gameLost;
    
public:
    GameState();
    
    // Getters
    GamePhase GetCurrentPhase() const { return currentPhase; }
    DayPhase GetDayPhase() const { return dayPhase; }
    int GetCurrentDay() const { return currentDay; }
    int GetSelectedPatient() const { return selectedPatient; }
    bool IsGameWon() const { return gameWon; }
    bool IsGameLost() const { return gameLost; }
    bool IsGameOver() const { return gameWon || gameLost; }
    
    // Setters
    void SetPhase(GamePhase phase) { currentPhase = phase; }
    void SetDayPhase(DayPhase phase) { dayPhase = phase; }
    void SetCurrentDay(int day) { currentDay = day; }
    void SetSelectedPatient(int patient) { selectedPatient = patient; }
    void SetGameWon(bool won) { gameWon = won; }
    void SetGameLost(bool lost) { gameLost = lost; }
    
    // Transições
    void StartNewGame();
    void StartNewDay();
    void CompleteDay();
    void TransitionToDusk();
    void TransitionToNight();
    
    // Verificações
    bool IsLastDay() const { return currentDay >= TOTAL_DAYS; }
    bool CanProgressToNextDay() const;
};

#endif // GAMESTATE_HPP