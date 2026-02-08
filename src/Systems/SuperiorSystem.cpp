#include "Systems/SuperiorSystem.hpp"
#include "Entities/Experimento.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

SuperiorSystem::SuperiorSystem()
    : cooldownTimer(MIN_COOLDOWN),
      gardenBlocked(false),
      panicActive(false),
      panicTimer(0.0f),
      lastAbility(SuperiorAbility::CHANGE_TEMPERATURES),
      isActive(false) {
}

void SuperiorSystem::Update(float deltaTime, bool frnd19Blocking) {
    // Atualizar timer de pânico se ativo
    if (panicActive) {
        panicTimer -= deltaTime;
        if (panicTimer <= 0.0f) {
            panicActive = false;
            panicTimer = 0.0f;
            std::cout << "[SUPERIOR] Pane Geral encerrada." << std::endl;
        }
    }
    
    // Cooldown do Superior
    if (cooldownTimer > 0.0f) {
        cooldownTimer -= deltaTime;
    }
    
    // Quando cooldown acabar, ativar habilidade aleatória
    if (cooldownTimer <= 0.0f) {
        ActivateRandomAbility();
        
        // Se Pane Geral e FRND19 está bloqueando, cancelar
        if (lastAbility == SuperiorAbility::GENERAL_PANIC && frnd19Blocking) {
            std::cout << "[SUPERIOR] Pane Geral BLOQUEADA por F-R.N.D.19!" << std::endl;
            panicActive = false;
            isActive = false;
        }
        
        // Resetar cooldown
        cooldownTimer = MIN_COOLDOWN;
    }
}

void SuperiorSystem::ActivateRandomAbility() {
    // Escolher habilidade aleatória (0, 1 ou 2)
    int choice = rand() % 3;
    
    switch (choice) {
        case 0:
            lastAbility = SuperiorAbility::CHANGE_TEMPERATURES;
            isActive = true;
            std::cout << "[SUPERIOR] Preparando \"Mudar Temperaturas\"..." << std::endl;
            break;
            
        case 1:
            lastAbility = SuperiorAbility::GENERAL_PANIC;
            ActivateGeneralPanic();
            break;
            
        case 2:
            lastAbility = SuperiorAbility::BLOCK_GARDEN;
            BlockGarden();
            break;
    }
}

void SuperiorSystem::ChangeTemperatures(std::vector<std::unique_ptr<Experimento>>& experiments) {
    if (!isActive || lastAbility != SuperiorAbility::CHANGE_TEMPERATURES) {
        return;
    }
    
    std::cout << "[SUPERIOR] Mudando temperaturas..." << std::endl;
    
    int changed = 0;
    for (auto& exp : experiments) {
        // 50% de chance de inverter temperatura
        if (rand() % 2 == 0) {
            // Inverter temperatura
            // (Experimento vai implementar ToggleTemperature())
            exp->ToggleTemperature();
            changed++;
        }
    }
    
    std::cout << "[SUPERIOR] " << changed << " temperaturas alteradas!" << std::endl;
    isActive = false;
}

void SuperiorSystem::ActivateGeneralPanic() {
    panicActive = true;
    panicTimer = 5.0f;  // 5 segundos de pânico
    isActive = true;
    
    std::cout << "[SUPERIOR] PANE GERAL ATIVADA! (5 segundos)" << std::endl;
    std::cout << "[AVISO] Todas as contencoes desativadas!" << std::endl;
}

void SuperiorSystem::BlockGarden() {
    gardenBlocked = true;
    isActive = true;
    
    std::cout << "[SUPERIOR] JARDIM BLOQUEADO!" << std::endl;
    std::cout << "[AVISO] Va para a Sala e hackeie as portas!" << std::endl;
}

void SuperiorSystem::UnblockGarden() {
    gardenBlocked = false;
    isActive = false;
    
    std::cout << "[SISTEMA] Jardim desbloqueado com sucesso!" << std::endl;
}

void SuperiorSystem::Reset() {
    cooldownTimer = MIN_COOLDOWN;
    gardenBlocked = false;
    panicActive = false;
    panicTimer = 0.0f;
    isActive = false;
}