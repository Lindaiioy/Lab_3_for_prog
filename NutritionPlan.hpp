#ifndef NUTRITIONPLAN_HPP
#define NUTRITIONPLAN_HPP

#include <string>
#include <vector>

class MealItem;
class Recipe;

class NutritionPlan {
public:
    std::string id;
    std::string date;
    std::vector<std::string> meals;
    std::string notes;

    double adjustWeightChangeTargetKg(double kg);
    void replaceMeal(const std::string& mealType, const Recipe& newRecipe);

    NutritionPlan();
    ~NutritionPlan();
};

#endif