#include "Systems/ContainmentSystem.hpp"
#include <iostream>

ContainmentSystem::ContainmentSystem()
    : oxygenMaskActive(false),
      oxygenMaskTimer(0.0f),
      uvLightActive(false),
      uvLightTimer(0.0f),
      uvLightHoldTime(0.0f),
      canResetTemperature(true),
      temperatureResetCooldown(0.0f),
      dionaeaFeedCount(0),
      containmentsDisabled(false),
      disabledTimer(0.0f) {
}

void ContainmentSystem::Update(float deltaTime) {
    // Atualizar máscara de oxigênio
    if (oxygenMaskActive) {
        oxygenMaskTimer -= deltaTime;
        if (oxygenMaskTimer <= 0.0f) {
            oxygenMaskTimer = 0.0f;
            oxygenMaskActive = false;
            std::cout << "[MASCARA] Oxigenio esgotado!" << std::endl;
        }
    }
    
    // Atualizar luz UV
    if (uvLightActive) {
        uvLightHoldTime += deltaTime;
    } else {
        uvLightHoldTime = 0.0f;
    }
    
    // Cooldown de temperatura
    if (temperatureResetCooldown > 0.0f) {
        temperatureResetCooldown -= deltaTime;
        if (temperatureResetCooldown <= 0.0f) {
            canResetTemperature = true;
        }
    }
    
    // Timer de contenções desabilitadas
    if (containmentsDisabled) {
        disabledTimer -= deltaTime;
        if (disabledTimer <= 0.0f) {
            containmentsDisabled = false;
            std::cout << "[CONTENCAO] Sistemas reativados!" << std::endl;
        }
    }
}

void ContainmentSystem::Reset() {
    oxygenMaskActive = false;
    oxygenMaskTimer = 0.0f;
    uvLightActive = false;
    uvLightTimer = 0.0f;
    uvLightHoldTime = 0.0f;
    canResetTemperature = true;
    temperatureResetCooldown = 0.0f;
    dionaeaFeedCount = 0;
    containmentsDisabled = false;
    disabledTimer = 0.0f;
}

void ContainmentSystem::ActivateMask() {
    if (containmentsDisabled) {
        std::cout << "[MASCARA] INDISPONIVEL - Pane Geral ativa!" << std::endl;
        return;
    }
    
    oxygenMaskActive = true;
    oxygenMaskTimer = MASK_DURATION;
    std::cout << "[MASCARA] Ativada! Oxigenio: " << (int)MASK_DURATION << " segundos" << std::endl;
}

void ContainmentSystem::DeactivateMask() {
    oxygenMaskActive = false;
    oxygenMaskTimer = 0.0f;
}

void ContainmentSystem::StartUVLight() {
    if (containmentsDisabled) {
        std::cout << "[LUZ UV] INDISPONIVEL - Pane Geral ativa!" << std::endl;
        return;
    }
    
    uvLightActive = true;
    std::cout << "[LUZ UV] Ativada! Segure por 5 segundos..." << std::endl;
}

void ContainmentSystem::StopUVLight() {
    uvLightActive = false;
    uvLightHoldTime = 0.0f;
}

void ContainmentSystem::ResetAllTemperatures() {
    if (!canResetTemperature) {
        std::cout << "[TEMPERATURA] Ainda em cooldown!" << std::endl;
        return;
    }
    
    if (containmentsDisabled) {
        std::cout << "[TEMPERATURA] INDISPONIVEL - Pane Geral ativa!" << std::endl;
        return;
    }
    
    canResetTemperature = false;
    temperatureResetCooldown = 30.0f;  // 30 segundos de cooldown
    std::cout << "[TEMPERATURA] Todas as temperaturas resetadas!" << std::endl;
}

void ContainmentSystem::FeedDionaea() {
    if (containmentsDisabled) {
        std::cout << "[DIONAEA] INDISPONIVEL - Pane Geral ativa!" << std::endl;
        return;
    }
    
    if (dionaeaFeedCount >= MAX_FEEDS) {
        std::cout << "[DIONAEA] Limite de alimentacoes atingido! (" << MAX_FEEDS << "/" << MAX_FEEDS << ")" << std::endl;
        return;
    }
    
    dionaeaFeedCount++;
    std::cout << "[DIONAEA] Alimentada! (" << dionaeaFeedCount << "/" << MAX_FEEDS << ")" << std::endl;
}

void ContainmentSystem::DisableAll(float duration) {
    containmentsDisabled = true;
    disabledTimer = duration;
    
    // Desativar tudo que estiver ativo
    oxygenMaskActive = false;
    uvLightActive = false;
    
    std::cout << "[CONTENCAO] PANE GERAL! Todas as contencoes desativadas por " 
              << (int)duration << " segundos!" << std::endl;
}

bool ContainmentSystem::AreContainmentsDisabled() const {
    return containmentsDisabled;
}