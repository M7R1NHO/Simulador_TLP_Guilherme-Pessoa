#include "Systems/DNASystem.hpp"
#include <iostream>

DNASystem::DNASystem() {
    Initialize();
}

void DNASystem::Initialize() {
    samples.clear();
    
    // Criar 4 slots para DNA (1 por experimento)
    for (int i = 1; i <= 4; i++) {
        DNASample sample;
        sample.experimentId = i;
        sample.collected = false;
        sample.name = "DNA Experimento " + std::to_string(i);
        samples.push_back(sample);
    }
    
    // Definir qual experimento precisa DNA em cada dia (1-4)
    // Dia 5 precisa de TODOS
    requiredDNAPerDay = {
        0,  // Índice 0 não usado
        2,  // Dia 1 precisa DNA do Experimento 2
        1,  // Dia 2 precisa DNA do Experimento 1
        4,  // Dia 3 precisa DNA do Experimento 4
        3,  // Dia 4 precisa DNA do Experimento 3
        0   // Dia 5 precisa de TODOS (tratado separadamente)
    };
}

void DNASystem::SetRequiredDNA(int day, int experimentId) {
    if (day >= 1 && day <= 5) {
        if (day < 5) {
            requiredDNAPerDay[day] = experimentId;
        }
    }
}

bool DNASystem::CollectDNA(int experimentId) {
    for (auto& sample : samples) {
        if (sample.experimentId == experimentId) {
            if (!sample.collected) {
                sample.collected = true;
                std::cout << "[DNA] Coletado: " << sample.name << std::endl;
                return true;
            } else {
                std::cout << "[DNA] Ja foi coletado!" << std::endl;
                return false;
            }
        }
    }
    
    std::cout << "[DNA] Experimento invalido!" << std::endl;
    return false;
}

bool DNASystem::HasDNA(int experimentId) const {
    for (const auto& sample : samples) {
        if (sample.experimentId == experimentId) {
            return sample.collected;
        }
    }
    return false;
}

void DNASystem::ClearDNA(int experimentId) {
    for (auto& sample : samples) {
        if (sample.experimentId == experimentId) {
            sample.collected = false;
        }
    }
}

void DNASystem::ClearAll() {
    for (auto& sample : samples) {
        sample.collected = false;
    }
}

bool DNASystem::HasRequiredDNA(int day) const {
    if (day < 1 || day > 5) return false;
    
    // Dia 5 especial: precisa de TODOS os DNAs
    if (day == 5) {
        return AllDNACollected();
    }
    
    // Dias 1-4: verifica se tem o DNA específico
    int requiredExp = requiredDNAPerDay[day];
    return HasDNA(requiredExp);
}

int DNASystem::GetRequiredDNAForDay(int day) const {
    if (day >= 1 && day < 5) {
        return requiredDNAPerDay[day];
    }
    return 0;  // Dia 5 retorna 0 (precisa de todos)
}

bool DNASystem::AllDNACollected() const {
    for (const auto& sample : samples) {
        if (!sample.collected) {
            return false;
        }
    }
    return true;
}

int DNASystem::GetCollectedCount() const {
    int count = 0;
    for (const auto& sample : samples) {
        if (sample.collected) {
            count++;
        }
    }
    return count;
}