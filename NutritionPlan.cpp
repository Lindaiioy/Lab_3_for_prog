#include "NutritionPlan.hpp"
#include "Recipe.hpp"

NutritionPlan::NutritionPlan() {}

NutritionPlan::~NutritionPlan() {}

double NutritionPlan::adjustWeightChangeTargetKg(double kg) {
    return kg;
}

void NutritionPlan::replaceMeal(const std::string& mealType, const Recipe& newRecipe) {
}