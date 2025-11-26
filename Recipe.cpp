#include "Recipe.hpp"
#include "UserProfile.hpp"

Recipe::Recipe() {}

Recipe::~Recipe() {}

std::string Recipe::scaleServings(double num) {
    return perServing;
}

bool Recipe::matchesPreferences(const UserProfile& profile) {
    return true;
}