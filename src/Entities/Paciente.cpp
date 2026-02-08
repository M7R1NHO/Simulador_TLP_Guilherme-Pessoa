#include "Entities/Paciente.hpp"
#include "Utils/Constants.hpp"

Paciente::Paciente(int patientId, Vector2 pos)
    : id(patientId),
      position(pos),
      isCured(false) {
    
    InitializePatientData();
}

void Paciente::InitializePatientData() {
    // Definir dados específicos por paciente
    switch (id) {
        case 1:
            name = "Paciente 001 - Ana Silva";
            description = "Infeccao bacterial rara";
            recipe = {
                "Nicotiana Normal",
                "Drosera Mutante",
                "DNA Experimento 2"
            };
            break;
            
        case 2:
            name = "Paciente 002 - Carlos Mendes";
            description = "Mutacao genetica tipo B";
            recipe = {
                "F-R.N.D.19 Mutante",
                "Dionaea",
                "Nicotiana Adubada",
                "DNA Experimento 1"
            };
            break;
            
        case 3:
            name = "Paciente 003 - Maria Costa";
            description = "Virus mutante desconhecido";
            recipe = {
                "Papoula Mutante",
                "Drosera Normal",
                "F-R.N.D.19 Adubada",
                "DNA Experimento 4"
            };
            break;
            
        case 4:
            name = "Paciente 004 - Pedro Santos";
            description = "Sindrome de rejeicao celular";
            recipe = {
                "Nicotiana Mutante Adubada",
                "Papoula Normal",
                "Drosera Mutante",
                "DNA Experimento 3"
            };
            break;
            
        case 5:
            name = "Paciente 005 - CASO CRITICO";
            description = "Multiplas infeccoes simultaneas";
            recipe = {
                "Dionaea",
                "F-R.N.D.19 Mutante Adubada",
                "Nicotiana Mutante",
                "Papoula Mutante",
                "DNA Experimento 1",
                "DNA Experimento 2",
                "DNA Experimento 3",
                "DNA Experimento 4"
            };
            break;
            
        default:
            name = "Paciente Desconhecido";
            description = "Erro no sistema";
            break;
    }
}

void Paciente::Render() {
    // Desenhar avatar do paciente
    Color patientColor = isCured ? COLOR_SUCCESS : (Color){100, 150, 200, 255};
    
    DrawCircleV(position, 40, patientColor);
    
    // Número do paciente
    std::string idText = std::to_string(id);
    DrawText(idText.c_str(), position.x - 8, position.y - 10, 30, WHITE);
    
    // Status
    if (isCured) {
        DrawText("CURADO", position.x - 30, position.y + 50, 12, COLOR_SUCCESS);
    }
    
    // Nome abaixo
    int nameWidth = MeasureText(name.c_str(), 14);
    DrawText(name.c_str(), position.x - nameWidth/2, position.y + 65, 14, COLOR_TEXT);
}

void Paciente::RenderInfo() {
    // Painel de informações (quando selecionado)
    int panelX = 50;
    int panelY = 100;
    int panelWidth = 400;
    int panelHeight = 300;
    
    DrawRectangle(panelX, panelY, panelWidth, panelHeight, COLOR_UI);
    DrawRectangleLines(panelX, panelY, panelWidth, panelHeight, COLOR_TEXT);
    
    // Nome
    DrawText(name.c_str(), panelX + 10, panelY + 10, 20, COLOR_TEXT);
    
    // Descrição
    DrawText("Condicao:", panelX + 10, panelY + 40, 16, COLOR_WARNING);
    DrawText(description.c_str(), panelX + 10, panelY + 60, 14, COLOR_TEXT);
    
    // Receita
    DrawText("Receita da Cura:", panelX + 10, panelY + 90, 18, COLOR_SUCCESS);
    
    int yOffset = 115;
    for (size_t i = 0; i < recipe.size(); i++) {
        std::string step = std::to_string(i + 1) + ") " + recipe[i];
        DrawText(step.c_str(), panelX + 15, panelY + yOffset, 14, COLOR_TEXT);
        yOffset += 22;
    }
}

bool Paciente::IsClicked(Vector2 mousePos) const {
    float distance = Vector2Distance(mousePos, position);
    return distance < 40.0f;  // Raio do círculo
}