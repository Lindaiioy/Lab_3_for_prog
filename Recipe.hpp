#pragma once

#include <memory>
#include <string>
#include <iostream>
#include "UserProfile.hpp"

class RecipeBase {
protected:
    std::string recipeType;
public:
    RecipeBase(const std::string& type = "General");
    RecipeBase(const RecipeBase& other);
    virtual ~RecipeBase();
    std::string getType() const;
};

class Recipe : public RecipeBase {
private:
    std::string perServing;
    std::unique_ptr<std::string> instructions;
    std::shared_ptr<UserProfile> associatedProfile;

public:
    Recipe();
    Recipe(const std::string& servingInfo);
    
    Recipe(const Recipe& other);
    Recipe& operator=(const Recipe& other);
    
    Recipe(Recipe&& other) noexcept;
    Recipe& operator=(Recipe&& other) noexcept;

    ~Recipe();

    std::string scaleServings(double num) const;
    bool matchesPreferences(const UserProfile& profile) const;

    bool operator==(const Recipe& other) const;
    bool operator!=(const Recipe& other) const;
    Recipe operator+(const Recipe& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Recipe& recipe);
};