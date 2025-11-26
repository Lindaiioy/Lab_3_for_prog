#include "Mascot.hpp"
#include "UserProfile.hpp"
#include "ProgressTracker.hpp"
#include "Workout.hpp"

Mascot::Mascot() : xp(0) {}

Mascot::~Mascot() {}

std::string Mascot::reactToWorkoutStart(const Workout& workoutStatus) {
    return "Let's go!";
}

std::string Mascot::getDailyMessage(const UserProfile& user, const ProgressTracker& progress) {
    return "Good morning!";
}