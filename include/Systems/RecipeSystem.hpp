#ifndef RECIPESYSTEM_HPP
#define RECIPESYSTEM_HPP

#include <string>
#include <vector>

struct RecipeIngredient {
    std::string name;
    bool collected;
};

struct Recipe {
    std::string recipeName;
    std::vector<RecipeIngredient> ingredients;
    int currentStep;
    bool isComplete;
};

class RecipeSystem {
private:
    Recipe currentRecipe;
    std::vector<Recipe> patientRecipes;  // 5 receitas (1 por paciente)

public:
    RecipeSystem();
    
    void Initialize();
    void LoadRecipe(int patientId);
    
    // Adicionar ingrediente (na ordem!)
    bool AddIngredient(const std::string& ingredientName);
    
    // Verificações
    bool IsRecipeComplete() const;
    std::string GetCurrentIngredientNeeded() const;
    int GetCurrentStep() const { return currentRecipe.currentStep; }
    int GetTotalSteps() const { return currentRecipe.ingredients.size(); }
    
    // Getters
    Recipe GetCurrentRecipe() const { return currentRecipe; }
    std::vector<RecipeIngredient> GetIngredients() const { return currentRecipe.ingredients; }
    
    // Reset
    void Reset();
    void ClearCurrentRecipe();

private:
    void InitializePatientRecipes();
};

#endif // RECIPESYSTEM_HPP