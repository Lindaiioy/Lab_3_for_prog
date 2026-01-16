#pragma once

#include <memory>
#include <string>
#include <map>
#include <iostream>
#include "Recipe.hpp"

class NutritionBase {
protected:
    std::string planType;
public:
    NutritionBase(const std::string& type = "General");
    NutritionBase(const NutritionBase& other);
    virtual ~NutritionBase();
    std::string getType() const;
};

class NutritionPlan : public NutritionBase {
private:
    std::map<std::string, std::shared_ptr<Recipe>> meals;
    std::unique_ptr<double> weightTarget;

public:
    NutritionPlan();
    NutritionPlan(const std::string& type);
    
    NutritionPlan(const NutritionPlan& other);
    NutritionPlan& operator=(const NutritionPlan& other);
    
    NutritionPlan(NutritionPlan&& other) noexcept;
    NutritionPlan& operator=(NutritionPlan&& other) noexcept;

    ~NutritionPlan();

    double adjustWeightChangeTargetKg(double kg);
    void replaceMeal(const std::string& mealType, const Recipe& newRecipe);

    bool operator==(const NutritionPlan& other) const;
    bool operator!=(const NutritionPlan& other) const;
    NutritionPlan operator+(const NutritionPlan& other) const;

    friend std::ostream& operator<<(std::ostream& os, const NutritionPlan& plan);
};