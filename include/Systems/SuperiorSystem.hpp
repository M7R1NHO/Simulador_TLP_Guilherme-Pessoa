#ifndef SUPERIORSYSTEM_HPP
#define SUPERIORSYSTEM_HPP

#include <vector>
#include <memory>

class Experimento;

enum class SuperiorAbility {
    CHANGE_TEMPERATURES,  // Mudar Temperaturas (50% chance por jaula)
    GENERAL_PANIC,        // Pane Geral (desativa contenções por 5s)
    BLOCK_GARDEN          // Bloquear Jardim (precisa hackear)
};

class SuperiorSystem {
private:
    float cooldownTimer;
    const float MIN_COOLDOWN = 20.0f;  // 20 segundos entre ações
    
    // Estado das habilidades
    bool gardenBlocked;
    bool panicActive;
    float panicTimer;
    
    SuperiorAbility lastAbility;
    bool isActive;

public:
    SuperiorSystem();
    
    void Update(float deltaTime, bool frnd19Blocking);
    void ActivateRandomAbility();
    
    // Habilidades específicas
    void ChangeTemperatures(std::vector<std::unique_ptr<Experimento>>& experiments);
    void ActivateGeneralPanic();
    void BlockGarden();
    void UnblockGarden();
    
    // Getters
    bool IsGardenBlocked() const { return gardenBlocked; }
    bool IsPanicActive() const { return panicActive; }
    float GetPanicTimeLeft() const { return panicTimer; }
    float GetCooldownTimer() const { return cooldownTimer; }
    bool IsActive() const { return isActive; }
    SuperiorAbility GetLastAbility() const { return lastAbility; }
    
    // Reset para novo dia
    void Reset();
};

#endif // SUPERIORSYSTEM_HPP