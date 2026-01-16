#include "Recipe.hpp"
#include <sstream>

RecipeBase::RecipeBase(const std::string& type) : recipeType(type) {}

RecipeBase::RecipeBase(const RecipeBase& other) : recipeType(other.recipeType) {}

RecipeBase::~RecipeBase() = default;

std::string RecipeBase::getType() const {
    return recipeType;
}

Recipe::Recipe() : RecipeBase("Recipe"), perServing("1 serving"), instructions(std::make_unique<std::string>("No instructions")) {}

Recipe::Recipe(const std::string& servingInfo) : RecipeBase("Recipe"), perServing(servingInfo), instructions(std::make_unique<std::string>("No instructions")) {}

Recipe::Recipe(const Recipe& other)
    : RecipeBase(other), perServing(other.perServing), 
      instructions(other.instructions ? std::make_unique<std::string>(*other.instructions) : nullptr),
      associatedProfile(other.associatedProfile) {}

Recipe& Recipe::operator=(const Recipe& other) {
    if (this != &other) {
        RecipeBase::operator=(other);
        perServing = other.perServing;
        if (other.instructions) {
            instructions = std::make_unique<std::string>(*other.instructions);
        } else {
            instructions.reset();
        }
        associatedProfile = other.associatedProfile;
    }
    return *this;
}

Recipe::Recipe(Recipe&& other) noexcept
    : RecipeBase(std::move(other)), perServing(std::move(other.perServing)), 
      instructions(std::move(other.instructions)),
      associatedProfile(std::move(other.associatedProfile)) {}

Recipe& Recipe::operator=(Recipe&& other) noexcept {
    if (this != &other) {
        RecipeBase::operator=(std::move(other));
        perServing = std::move(other.perServing);
        instructions = std::move(other.instructions);
        associatedProfile = std::move(other.associatedProfile);
    }
    return *this;
}

Recipe::~Recipe() = default;

std::string Recipe::scaleServings(double num) const {
    std::stringstream ss;
    ss << num << " x " << perServing;
    std::string scaled = ss.str();
    size_t pos = scaled.find("x");
    if (pos != std::string::npos) {
        scaled.replace(pos, 1, "times");
    }
    return scaled;
}

bool Recipe::matchesPreferences(const UserProfile& profile) const {
    std::string prefs = profile.getProfileInfo();
    if (prefs.find(perServing) != std::string::npos) {
        return true;
    }
    return false;
}

bool Recipe::operator==(const Recipe& other) const {
    return perServing == other.perServing;
}

bool Recipe::operator!=(const Recipe& other) const {
    return !(*this == other);
}

Recipe Recipe::operator+(const Recipe& other) const {
    std::string combinedServing = perServing + " + " + other.perServing;
    return Recipe(combinedServing);
}

std::ostream& operator<<(std::ostream& os, const Recipe& recipe) {
    os << "Recipe: " << recipe.perServing;
    if (recipe.instructions) {
        os << " - " << *recipe.instructions;
    }
    return os;
}