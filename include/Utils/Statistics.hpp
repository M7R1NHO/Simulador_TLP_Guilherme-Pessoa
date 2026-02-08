#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include <string>

class Statistics {
private:
    // Tempo
    float totalPlayTime;
    
    // Plantas
    int plantsCollected;
    int plantsMutated;
    int plantsFertilized;
    int plantsLost;
    int plantsReplanted;
    
    // Experimentos
    int dnaCollected;
    int experimentsKilled;
    
    // Contenção
    int timesUsedMask;
    int timesUsedUV;
    int timesFedDionaea;
    
    // Superior
    int superiorActivations;
    int hacksCompleted;
    
    // Dias
    int daysCompleted;
    int patientsHealed;

public:
    Statistics();
    
    void Reset();
    void Update(float deltaTime);
    
    // Incrementos
    void IncrementPlantsCollected() { plantsCollected++; }
    void IncrementPlantsMutated() { plantsMutated++; }
    void IncrementPlantsFertilized() { plantsFertilized++; }
    void IncrementPlantsLost() { plantsLost++; }
    void IncrementPlantsReplanted() { plantsReplanted++; }
    void IncrementDNACollected() { dnaCollected++; }
    void IncrementExperimentsKilled() { experimentsKilled++; }
    void IncrementMaskUsage() { timesUsedMask++; }
    void IncrementUVUsage() { timesUsedUV++; }
    void IncrementDionaeaFeed() { timesFedDionaea++; }
    void IncrementSuperiorActivation() { superiorActivations++; }
    void IncrementHacks() { hacksCompleted++; }
    void IncrementDaysCompleted() { daysCompleted++; }
    void IncrementPatientsHealed() { patientsHealed++; }
    
    // Getters
    float GetTotalPlayTime() const { return totalPlayTime; }
    int GetPlantsCollected() const { return plantsCollected; }
    int GetPlantsMutated() const { return plantsMutated; }
    int GetPlantsLost() const { return plantsLost; }
    int GetDNACollected() const { return dnaCollected; }
    int GetDaysCompleted() const { return daysCompleted; }
    int GetPatientsHealed() const { return patientsHealed; }
    
    // Exibir estatísticas
    void Render();
    std::string GetSummary() const;
};

#endif // STATISTICS_HPP