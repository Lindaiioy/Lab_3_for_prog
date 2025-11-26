#ifndef RECIPE_HPP
#define RECIPE_HPP

#include <string>
#include <set>
#include <vector>

class UserProfile;

class Recipe {
public:
    std::string id;
    std::string name;
    std::string perServing;
    std::set<std::string> tags;
    std::set<std::string> allergens;
    std::vector<std::string> ingredients;

    std::string scaleServings(double num);
    bool matchesPreferences(const UserProfile& profile);

    Recipe();
    ~Recipe();
};

#endif