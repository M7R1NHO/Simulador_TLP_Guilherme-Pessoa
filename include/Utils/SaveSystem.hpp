#ifndef SAVESYSTEM_HPP
#define SAVESYSTEM_HPP

#include <string>
#include <vector>

struct SaveData {
    // Progresso do jogo
    int currentDay;              // 1-5
    int currentPatient;          // 1-5
    bool patientsCompleted[5];   // Quais pacientes foram curados
    
    // Experimentos
    int experimentStress[4];     // Stress de cada experimento
    int experimentIrritation[4]; // Irritação de cada experimento
    bool experimentSedated[4];   // Se está sedado
    
    // DNA coletado
    bool dnaCollected[4];        // DNA de cada experimento
    
    // Estatísticas
    int totalPlayTime;           // Segundos jogados
    int plantsLost;              // Quantas plantas morreram
    int timesUsedMask;           // Vezes que usou máscara
    
    // Validação
    int checksum;                // Para verificar se save é válido
};

class SaveSystem {
private:
    std::string savePath;
    
    int CalculateChecksum(const SaveData& data) const;
    bool ValidateChecksum(const SaveData& data) const;

public:
    SaveSystem();
    
    // Save/Load
    bool SaveGame(const SaveData& data);
    bool LoadGame(SaveData& data);
    bool SaveExists() const;
    void DeleteSave();
    
    // Criar save vazio
    SaveData CreateNewSave() const;
};

#endif // SAVESYSTEM_HPP