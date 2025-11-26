#include "WorkoutPlan.hpp"
#include "UserProfile.hpp"
#include "Workout.hpp"
#include "ExerciseCategory.hpp"

WorkoutPlan::WorkoutPlan() : userProfile(nullptr) {}

WorkoutPlan::~WorkoutPlan() {}

void WorkoutPlan::generatePersonalizedParams(const ExerciseCategory& category) {
}

void WorkoutPlan::adaptOnFeedback(const std::string& feedback) {
}

std::vector<Workout> WorkoutPlan::getUpcoming(int count) {
    return {};
}