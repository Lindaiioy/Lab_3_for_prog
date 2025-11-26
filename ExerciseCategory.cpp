#include "ExerciseCategory.hpp"
#include "Exercise.hpp"
#include "UserProfile.hpp"

ExerciseCategory::ExerciseCategory() {}

ExerciseCategory::~ExerciseCategory() {}

std::vector<Exercise> ExerciseCategory::filterByGoal(const std::string& goal, const std::set<std::string>& equipment, const std::string& level) {
    return {};
}

std::vector<Exercise> ExerciseCategory::recommendForSlot(const std::string& workoutSlot, const UserProfile& user, const std::string& history) {
    return {};
}