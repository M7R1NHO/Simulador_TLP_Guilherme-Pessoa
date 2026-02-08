#include "Utils/Statistics.hpp"
#include "Utils/Constants.hpp"
#include <sstream>
#include <iomanip>

Statistics::Statistics()
    : totalPlayTime(0.0f),
      plantsCollected(0),
      plantsMutated(0),
      plantsFertilized(0),
      plantsLost(0),
      plantsReplanted(0),
      dnaCollected(0),
      experimentsKilled(0),
      timesUsedMask(0),
      timesUsedUV(0),
      timesFedDionaea(0),
      superiorActivations(0),
      hacksCompleted(0),
      daysCompleted(0),
      patientsHealed(0) {
}

void Statistics::Reset() {
    totalPlayTime = 0.0f;
    plantsCollected = 0;
    plantsMutated = 0;
    plantsFertilized = 0;
    plantsLost = 0;
    plantsReplanted = 0;
    dnaCollected = 0;
    experimentsKilled = 0;
    timesUsedMask = 0;
    timesUsedUV = 0;
    timesFedDionaea = 0;
    superiorActivations = 0;
    hacksCompleted = 0;
    daysCompleted = 0;
    patientsHealed = 0;
}

void Statistics::Update(float deltaTime) {
    totalPlayTime += deltaTime;
}

void Statistics::Render() {
    // Painel de estatísticas
    int panelX = SCREEN_WIDTH / 2 - 300;
    int panelY = 100;
    int panelWidth = 600;
    int panelHeight = 500;
    
    DrawRectangle(panelX, panelY, panelWidth, panelHeight, COLOR_UI);
    DrawRectangleLines(panelX, panelY, panelWidth, panelHeight, COLOR_TEXT);
    
    // Título
    DrawText("ESTATISTICAS DO JOGO", panelX + 20, panelY + 20, 28, COLOR_TEXT);
    
    int yOffset = 70;
    int lineHeight = 30;
    
    // Tempo
    int minutes = (int)(totalPlayTime / 60.0f);
    int seconds = (int)totalPlayTime % 60;
    std::string timeText = "Tempo Total: " + std::to_string(minutes) + "m " + std::to_string(seconds) + "s";
    DrawText(timeText.c_str(), panelX + 20, panelY + yOffset, 20, COLOR_WARNING);
    yOffset += lineHeight;
    
    // Progresso
    std::string daysText = "Dias Completados: " + std::to_string(daysCompleted) + "/5";
    DrawText(daysText.c_str(), panelX + 20, panelY + yOffset, 20, COLOR_TEXT);
    yOffset += lineHeight;
    
    std::string patientsText = "Pacientes Curados: " + std::to_string(patientsHealed) + "/5";
    DrawText(patientsText.c_str(), panelX + 20, panelY + yOffset, 20, COLOR_TEXT);
    yOffset += lineHeight + 10;
    
    // Plantas
    DrawText("PLANTAS:", panelX + 20, panelY + yOffset, 22, COLOR_SUCCESS);
    yOffset += lineHeight;
    
    DrawText(("Coletadas: " + std::to_string(plantsCollected)).c_str(), 
             panelX + 40, panelY + yOffset, 18, COLOR_TEXT);
    yOffset += lineHeight - 5;
    
    DrawText(("Mutadas: " + std::to_string(plantsMutated)).c_str(), 
             panelX + 40, panelY + yOffset, 18, COLOR_TEXT);
    yOffset += lineHeight - 5;
    
    DrawText(("Perdidas: " + std::to_string(plantsLost)).c_str(), 
             panelX + 40, panelY + yOffset, 18, COLOR_TEXT);
    yOffset += lineHeight + 10;
    
    // Experimentos
    DrawText("EXPERIMENTOS:", panelX + 20, panelY + yOffset, 22, BLUE);
    yOffset += lineHeight;
    
    DrawText(("DNA Coletado: " + std::to_string(dnaCollected)).c_str(), 
             panelX + 40, panelY + yOffset, 18, COLOR_TEXT);
    yOffset += lineHeight - 5;
    
    DrawText(("Mortos: " + std::to_string(experimentsKilled)).c_str(), 
             panelX + 40, panelY + yOffset, 18, COLOR_TEXT);
    yOffset += lineHeight + 10;
    
    // Contenção
    DrawText("CONTENCAO:", panelX + 20, panelY + yOffset, 22, COLOR_WARNING);
    yOffset += lineHeight;
    
    DrawText(("Mascaras Usadas: " + std::to_string(timesUsedMask)).c_str(), 
             panelX + 40, panelY + yOffset, 18, COLOR_TEXT);
    yOffset += lineHeight - 5;
    
    DrawText(("Luz UV Usada: " + std::to_string(timesUsedUV)).c_str(), 
             panelX + 40, panelY + yOffset, 18, COLOR_TEXT);
    yOffset += lineHeight - 5;
    
    DrawText(("Dionaea Alimentada: " + std::to_string(timesFedDionaea)).c_str(), 
             panelX + 40, panelY + yOffset, 18, COLOR_TEXT);
    yOffset += lineHeight + 10;
    
    // Superior
    DrawText("SUPERIOR:", panelX + 20, panelY + yOffset, 22, COLOR_DANGER);
    yOffset += lineHeight;
    
    DrawText(("Ativacoes: " + std::to_string(superiorActivations)).c_str(), 
             panelX + 40, panelY + yOffset, 18, COLOR_TEXT);
    yOffset += lineHeight - 5;
    
    DrawText(("Hacks Completos: " + std::to_string(hacksCompleted)).c_str(), 
             panelX + 40, panelY + yOffset, 18, COLOR_TEXT);
}

std::string Statistics::GetSummary() const {
    std::stringstream ss;
    
    ss << "=== ESTATISTICAS FINAIS ===" << std::endl;
    ss << "Tempo Total: " << (int)(totalPlayTime / 60) << "m " << (int)totalPlayTime % 60 << "s" << std::endl;
    ss << "Dias Completados: " << daysCompleted << "/5" << std::endl;
    ss << "Pacientes Curados: " << patientsHealed << "/5" << std::endl;
    ss << std::endl;
    ss << "Plantas Coletadas: " << plantsCollected << std::endl;
    ss << "Plantas Mutadas: " << plantsMutated << std::endl;
    ss << "Plantas Perdidas: " << plantsLost << std::endl;
    ss << std::endl;
    ss << "DNA Coletado: " << dnaCollected << std::endl;
    ss << "Experimentos Mortos: " << experimentsKilled << std::endl;
    ss << std::endl;
    ss << "Mascaras Usadas: " << timesUsedMask << std::endl;
    ss << "Superior Ativacoes: " << superiorActivations << std::endl;
    
    return ss.str();
}