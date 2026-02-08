#include "Systems/RecipeSystem.hpp"
#include <iostream>

RecipeSystem::RecipeSystem() {
    Initialize();
}

void RecipeSystem::Initialize() {
    InitializePatientRecipes();
    currentRecipe.currentStep = 0;
    currentRecipe.isComplete = false;
}

void RecipeSystem::InitializePatientRecipes() {
    patientRecipes.clear();
    
    // PACIENTE 1
    Recipe recipe1;
    recipe1.recipeName = "Cura - Paciente 1";
    recipe1.ingredients = {
        {"Nicotiana Normal", false},
        {"Drosera Mutante", false},
        {"DNA Experimento 2", false}
    };
    recipe1.currentStep = 0;
    recipe1.isComplete = false;
    patientRecipes.push_back(recipe1);
    
    // PACIENTE 2
    Recipe recipe2;
    recipe2.recipeName = "Cura - Paciente 2";
    recipe2.ingredients = {
        {"F-R.N.D.19 Mutante", false},
        {"Dionaea", false},
        {"Nicotiana Adubada", false},
        {"DNA Experimento 1", false}
    };
    recipe2.currentStep = 0;
    recipe2.isComplete = false;
    patientRecipes.push_back(recipe2);
    
    // PACIENTE 3
    Recipe recipe3;
    recipe3.recipeName = "Cura - Paciente 3";
    recipe3.ingredients = {
        {"Papoula Mutante", false},
        {"Drosera Normal", false},
        {"F-R.N.D.19 Adubada", false},
        {"DNA Experimento 4", false}
    };
    recipe3.currentStep = 0;
    recipe3.isComplete = false;
    patientRecipes.push_back(recipe3);
    
    // PACIENTE 4
    Recipe recipe4;
    recipe4.recipeName = "Cura - Paciente 4";
    recipe4.ingredients = {
        {"Nicotiana Mutante Adubada", false},
        {"Papoula Normal", false},
        {"Drosera Mutante", false},
        {"DNA Experimento 3", false}
    };
    recipe4.currentStep = 0;
    recipe4.isComplete = false;
    patientRecipes.push_back(recipe4);
    
    // PACIENTE 5 (ESPECIAL - Todos os DNAs)
    Recipe recipe5;
    recipe5.recipeName = "Cura - Paciente 5 (CRITICO)";
    recipe5.ingredients = {
        {"Dionaea", false},
        {"F-R.N.D.19 Mutante Adubada", false},
        {"Nicotiana Mutante", false},
        {"Papoula Mutante", false},
        {"DNA Experimento 1", false},
        {"DNA Experimento 2", false},
        {"DNA Experimento 3", false},
        {"DNA Experimento 4", false}
    };
    recipe5.currentStep = 0;
    recipe5.isComplete = false;
    patientRecipes.push_back(recipe5);
}

void RecipeSystem::LoadRecipe(int patientId) {
    if (patientId < 1 || patientId > 5) {
        std::cerr << "[RECEITA] ID de paciente invalido: " << patientId << std::endl;
        return;
    }
    
    currentRecipe = patientRecipes[patientId - 1];
    currentRecipe.currentStep = 0;
    currentRecipe.isComplete = false;
    
    // Resetar todos os ingredientes
    for (auto& ingredient : currentRecipe.ingredients) {
        ingredient.collected = false;
    }
    
    std::cout << "[RECEITA] Carregada para Paciente " << patientId << std::endl;
    std::cout << "[RECEITA] Total de ingredientes: " << currentRecipe.ingredients.size() << std::endl;
}

bool RecipeSystem::AddIngredient(const std::string& ingredientName) {
    if (currentRecipe.isComplete) {
        std::cout << "[RECEITA] Ja esta completa!" << std::endl;
        return false;
    }
    
    // Verificar se estamos no passo correto
    if (currentRecipe.currentStep >= (int)currentRecipe.ingredients.size()) {
        std::cout << "[RECEITA] Todos os ingredientes ja foram adicionados!" << std::endl;
        return false;
    }
    
    // Ingrediente esperado neste passo
    std::string expectedIngredient = currentRecipe.ingredients[currentRecipe.currentStep].name;
    
    if (ingredientName == expectedIngredient) {
        // Correto!
        currentRecipe.ingredients[currentRecipe.currentStep].collected = true;
        currentRecipe.currentStep++;
        
        std::cout << "[RECEITA] ✓ Ingrediente correto! (" 
                  << currentRecipe.currentStep << "/" 
                  << currentRecipe.ingredients.size() << ")" << std::endl;
        
        // Verificar se completou
        if (currentRecipe.currentStep >= (int)currentRecipe.ingredients.size()) {
            currentRecipe.isComplete = true;
            std::cout << "[RECEITA] ★ RECEITA COMPLETA! ★" << std::endl;
        }
        
        return true;
    } else {
        // Errado!
        std::cout << "[RECEITA] ✗ Ingrediente ERRADO!" << std::endl;
        std::cout << "[RECEITA] Esperado: " << expectedIngredient << std::endl;
        std::cout << "[RECEITA] Recebido: " << ingredientName << std::endl;
        return false;
    }
}

bool RecipeSystem::IsRecipeComplete() const {
    return currentRecipe.isComplete;
}

std::string RecipeSystem::GetCurrentIngredientNeeded() const {
    if (currentRecipe.currentStep >= (int)currentRecipe.ingredients.size()) {
        return "RECEITA COMPLETA";
    }
    
    return currentRecipe.ingredients[currentRecipe.currentStep].name;
}

void RecipeSystem::Reset() {
    currentRecipe.currentStep = 0;
    currentRecipe.isComplete = false;
    
    for (auto& ingredient : currentRecipe.ingredients) {
        ingredient.collected = false;
    }
}

void RecipeSystem::ClearCurrentRecipe() {
    currentRecipe.ingredients.clear();
    currentRecipe.currentStep = 0;
    currentRecipe.isComplete = false;
}