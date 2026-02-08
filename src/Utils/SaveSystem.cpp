#include "Utils/SaveSystem.hpp"
#include "Utils/Constants.hpp"
#include <fstream>
#include <iostream>
#include <cstring>

SaveSystem::SaveSystem() {
    savePath = SAVE_PATH + "game.sav";
}

bool SaveSystem::SaveGame(const SaveData& data) {
    // Criar cópia com checksum
    SaveData dataToSave = data;
    dataToSave.checksum = CalculateChecksum(data);
    
    // Abrir arquivo binário
    std::ofstream file(savePath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "[SAVE] Erro ao criar arquivo de save!" << std::endl;
        return false;
    }
    
    // Escrever dados
    file.write(reinterpret_cast<const char*>(&dataToSave), sizeof(SaveData));
    file.close();
    
    std::cout << "[SAVE] Jogo salvo com sucesso! (Dia " << data.currentDay << ")" << std::endl;
    return true;
}

bool SaveSystem::LoadGame(SaveData& data) {
    if (!SaveExists()) {
        std::cerr << "[SAVE] Arquivo de save nao encontrado!" << std::endl;
        return false;
    }
    
    // Abrir arquivo
    std::ifstream file(savePath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "[SAVE] Erro ao abrir arquivo de save!" << std::endl;
        return false;
    }
    
    // Ler dados
    file.read(reinterpret_cast<char*>(&data), sizeof(SaveData));
    file.close();
    
    // Validar checksum
    if (!ValidateChecksum(data)) {
        std::cerr << "[SAVE] Arquivo corrompido! Checksum invalido." << std::endl;
        return false;
    }
    
    std::cout << "[SAVE] Jogo carregado! (Dia " << data.currentDay << ")" << std::endl;
    return true;
}

bool SaveSystem::SaveExists() const {
    std::ifstream file(savePath);
    return file.good();
}

void SaveSystem::DeleteSave() {
    if (SaveExists()) {
        std::remove(savePath.c_str());
        std::cout << "[SAVE] Save deletado." << std::endl;
    }
}

SaveData SaveSystem::CreateNewSave() const {
    SaveData data;
    
    data.currentDay = 1;
    data.currentPatient = 0;
    
    for (int i = 0; i < 5; i++) {
        data.patientsCompleted[i] = false;
    }
    
    for (int i = 0; i < 4; i++) {
        data.experimentStress[i] = 50;
        data.experimentIrritation[i] = 50;
        data.experimentSedated[i] = false;
        data.dnaCollected[i] = false;
    }
    
    data.totalPlayTime = 0;
    data.plantsLost = 0;
    data.timesUsedMask = 0;
    data.checksum = 0;
    
    return data;
}

int SaveSystem::CalculateChecksum(const SaveData& data) const {
    // Checksum simples: soma de todos os valores importantes
    int sum = 0;
    
    sum += data.currentDay;
    sum += data.currentPatient;
    
    for (int i = 0; i < 5; i++) {
        sum += data.patientsCompleted[i] ? 1 : 0;
    }
    
    for (int i = 0; i < 4; i++) {
        sum += data.experimentStress[i];
        sum += data.experimentIrritation[i];
        sum += data.experimentSedated[i] ? 1 : 0;
        sum += data.dnaCollected[i] ? 1 : 0;
    }
    
    sum += data.totalPlayTime;
    sum += data.plantsLost;
    sum += data.timesUsedMask;
    
    // Multiplicar por número mágico
    return sum * 7919;  // Número primo
}

bool SaveSystem::ValidateChecksum(const SaveData& data) const {
    int calculatedChecksum = CalculateChecksum(data);
    return calculatedChecksum == data.checksum;
}