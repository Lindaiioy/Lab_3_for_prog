#include "ProgressTracker.hpp"

ProgressTracker::ProgressTracker() : streak(0), bestStreak(0) {}

ProgressTracker::~ProgressTracker() {}

double ProgressTracker::getAchievementPercent(const std::string& dateInterval) {
    return 0.0;
}

double ProgressTracker::updateFromWorkout(const std::string& result) {
    return 0.0;
}

double ProgressTracker::estimateIMAX(const std::string& exerciseId) {
    return 0.0;
}