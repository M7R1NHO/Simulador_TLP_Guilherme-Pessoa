#ifndef DNASYSTEM_HPP
#define DNASYSTEM_HPP

#include <vector>
#include <string>

struct DNASample {
    int experimentId;      // 1-4
    bool collected;
    std::string name;      // "DNA Experimento 1"
};

class DNASystem {
private:
    std::vector<DNASample> samples;
    std::vector<int> requiredDNAPerDay;  // Qual experimento precisa DNA em cada dia
    
public:
    DNASystem();
    
    void Initialize();
    void SetRequiredDNA(int day, int experimentId);
    
    // Coleta
    bool CollectDNA(int experimentId);
    bool HasDNA(int experimentId) const;
    void ClearDNA(int experimentId);
    void ClearAll();
    
    // Verificações
    bool HasRequiredDNA(int day) const;
    int GetRequiredDNAForDay(int day) const;
    bool AllDNACollected() const;  // Para dia 5
    
    // Getters
    std::vector<DNASample> GetAllSamples() const { return samples; }
    int GetCollectedCount() const;
};

#endif // DNASYSTEM_HPP