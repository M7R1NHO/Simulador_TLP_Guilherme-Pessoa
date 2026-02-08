#ifndef CONTAINMENTSYSTEM_HPP
#define CONTAINMENTSYSTEM_HPP

class ContainmentSystem {
private:
    // Máscara de Oxigênio
    bool oxygenMaskActive;
    float oxygenMaskTimer;
    const float MASK_DURATION = 25.0f;
    
    // Luz Ultravioleta
    bool uvLightActive;
    float uvLightTimer;
    float uvLightHoldTime;
    const float UV_REQUIRED_TIME = 5.0f;
    
    // Temperatura (reajustar todas)
    bool canResetTemperature;
    float temperatureResetCooldown;
    
    // Dionaea Feed
    int dionaeaFeedCount;
    const int MAX_FEEDS = 3;

public:
    ContainmentSystem();
    
    void Update(float deltaTime);
    void Reset();  // Reset para novo dia
    
    // Máscara
    void ActivateMask();
    void DeactivateMask();
    bool IsMaskActive() const { return oxygenMaskActive; }
    float GetMaskTimeLeft() const { return oxygenMaskTimer; }
    
    // Luz UV
    void StartUVLight();
    void StopUVLight();
    bool IsUVActive() const { return uvLightActive; }
    bool IsUVComplete() const { return uvLightHoldTime >= UV_REQUIRED_TIME; }
    float GetUVProgress() const { return uvLightHoldTime / UV_REQUIRED_TIME; }
    
    // Temperatura
    void ResetAllTemperatures();
    bool CanResetTemperatures() const { return canResetTemperature; }
    
    // Dionaea
    bool CanFeedDionaea() const { return dionaeaFeedCount < MAX_FEEDS; }
    void FeedDionaea();
    int GetDionaeaFeedCount() const { return dionaeaFeedCount; }
    
    // Verificar se contenções estão desabilitadas (Pane Geral)
    void DisableAll(float duration);
    bool AreContainmentsDisabled() const;

private:
    bool containmentsDisabled;
    float disabledTimer;
};

#endif // CONTAINMENTSYSTEM_HPP