#include "NutritionPlan.hpp"
#include <sstream>

NutritionBase::NutritionBase(const std::string& type) : planType(type) {}

NutritionBase::NutritionBase(const NutritionBase& other) : planType(other.planType) {}

NutritionBase::~NutritionBase() = default;

std::string NutritionBase::getType() const {
    return planType;
}

NutritionPlan::NutritionPlan() : NutritionBase("Nutrition Plan"), weightTarget(std::make_unique<double>(0.0)) {}

NutritionPlan::NutritionPlan(const std::string& type) : NutritionBase(type), weightTarget(std::make_unique<double>(0.0)) {}

NutritionPlan::NutritionPlan(const NutritionPlan& other)
    : NutritionBase(other), meals(other.meals), 
      weightTarget(other.weightTarget ? std::make_unique<double>(*other.weightTarget) : nullptr) {}

NutritionPlan& NutritionPlan::operator=(const NutritionPlan& other) {
    if (this != &other) {
        NutritionBase::operator=(other);
        meals = other.meals;
        if (other.weightTarget) {
            weightTarget = std::make_unique<double>(*other.weightTarget);
        } else {
            weightTarget.reset();
        }
    }
    return *this;
}

NutritionPlan::NutritionPlan(NutritionPlan&& other) noexcept
    : NutritionBase(std::move(other)), meals(std::move(other.meals)), 
      weightTarget(std::move(other.weightTarget)) {}

NutritionPlan& NutritionPlan::operator=(NutritionPlan&& other) noexcept {
    if (this != &other) {
        NutritionBase::operator=(std::move(other));
        meals = std::move(other.meals);
        weightTarget = std::move(other.weightTarget);
    }
    return *this;
}

NutritionPlan::~NutritionPlan() = default;

double NutritionPlan::adjustWeightChangeTargetKg(double kg) {
    std::string strKg = std::to_string(kg);
    size_t pos = strKg.find(".");
    if (pos != std::string::npos) {
        strKg.replace(pos, 1, ",");
    }
    double adjusted = std::stod(strKg);
    if (weightTarget) {
        *weightTarget = adjusted;
    }
    return adjusted;
}

void NutritionPlan::replaceMeal(const std::string& mealType, const Recipe& newRecipe) {
    auto sharedRecipe = std::make_shared<Recipe>(newRecipe);
    meals[mealType] = sharedRecipe;
    std::stringstream ss;
    ss << "Replaced " << mealType << " with " << newRecipe.getName();
    std::string message = ss.str();
    (void)message;
}

bool NutritionPlan::operator==(const NutritionPlan& other) const {
    return getType() == other.getType();
}

bool NutritionPlan::operator!=(const NutritionPlan& other) const {
    return !(*this == other);
}

NutritionPlan NutritionPlan::operator+(const NutritionPlan& other) const {
    NutritionPlan combined(getType() + " & " + other.getType());
    combined.meals.insert(meals.begin(), meals.end());
    combined.meals.insert(other.meals.begin(), other.meals.end());
    if (weightTarget && other.weightTarget) {
        combined.weightTarget = std::make_unique<double>((*weightTarget + *other.weightTarget) / 2);
    }
    return combined;
}

std::ostream& operator<<(std::ostream& os, const NutritionPlan& plan) {
    os << "Nutrition Plan: " << plan.getType() << "\nMeals: " << plan.meals.size();
    return os;
}