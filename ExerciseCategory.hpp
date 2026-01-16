#pragma once

#include <memory>
#include <vector>
#include <string>
#include <set>
#include <iostream>
#include "Exercise.hpp"
#include "UserProfile.hpp"

class CategoryBase {
protected:
    std::string categoryName;
public:
    CategoryBase(const std::string& name = "General");
    CategoryBase(const CategoryBase& other);
    virtual ~CategoryBase();
    std::string getCategoryName() const;
};

class ExerciseCategory : public CategoryBase {
private:
    std::vector<std::shared_ptr<Exercise>> exercises;
    std::unique_ptr<std::string> description;

public:
    ExerciseCategory();
    ExerciseCategory(const std::string& name, const std::string& desc);
    
    ExerciseCategory(const ExerciseCategory& other);
    ExerciseCategory& operator=(const ExerciseCategory& other);
    
    ExerciseCategory(ExerciseCategory&& other) noexcept;
    ExerciseCategory& operator=(ExerciseCategory&& other) noexcept;

    ~ExerciseCategory();

    std::vector<Exercise> filterByGoal(const std::string& goal, const std::set<std::string>& equipment, const std::string& level) const;
    std::vector<Exercise> recommendForSlot(const std::string& workoutSlot, const UserProfile& user, const std::string& history) const;

    bool operator==(const ExerciseCategory& other) const;
    bool operator!=(const ExerciseCategory& other) const;
    ExerciseCategory operator+(const ExerciseCategory& other) const;

    friend std::ostream& operator<<(std::ostream& os, const ExerciseCategory& cat);
};