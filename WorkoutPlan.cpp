#include "WorkoutPlan.hpp"
#include <sstream>

PlanBase::PlanBase(const std::string& name) : planName(name) {}

PlanBase::PlanBase(const PlanBase& other) : planName(other.planName) {}

PlanBase::~PlanBase() = default;

std::string PlanBase::getPlanName() const {
    return planName;
}

WorkoutPlan::WorkoutPlan() : PlanBase("Workout Plan"), userProfile(nullptr) {}

WorkoutPlan::WorkoutPlan(const std::string& name) : PlanBase(name), userProfile(nullptr) {}

WorkoutPlan::WorkoutPlan(const WorkoutPlan& other)
    : PlanBase(other), upcomingWorkouts(other.upcomingWorkouts), 
      userProfile(other.userProfile ? std::make_unique<UserProfile>(*other.userProfile) : nullptr) {}

WorkoutPlan& WorkoutPlan::operator=(const WorkoutPlan& other) {
    if (this != &other) {
        PlanBase::operator=(other);
        upcomingWorkouts = other.upcomingWorkouts;
        if (other.userProfile) {
            userProfile = std::make_unique<UserProfile>(*other.userProfile);
        } else {
            userProfile.reset();
        }
    }
    return *this;
}

WorkoutPlan::WorkoutPlan(WorkoutPlan&& other) noexcept
    : PlanBase(std::move(other)), upcomingWorkouts(std::move(other.upcomingWorkouts)), 
      userProfile(std::move(other.userProfile)) {}

WorkoutPlan& WorkoutPlan::operator=(WorkoutPlan&& other) noexcept {
    if (this != &other) {
        PlanBase::operator=(std::move(other));
        upcomingWorkouts = std::move(other.upcomingWorkouts);
        userProfile = std::move(other.userProfile);
    }
    return *this;
}

WorkoutPlan::~WorkoutPlan() = default;

void WorkoutPlan::generatePersonalizedParams(const ExerciseCategory& category) {
    std::string params = "Params for " + category.getCategoryName();
    size_t pos = params.find("for");
    if (pos != std::string::npos) {
        params.replace(pos, 3, "based on");
    }
    (void)params;
}

void WorkoutPlan::adaptOnFeedback(const std::string& feedback) {
    std::stringstream ss;
    ss << "Adapted based on: " << feedback;
    std::string message = ss.str();
    message += "!";
}

std::vector<Workout> WorkoutPlan::getUpcoming(int count) const {
    std::vector<Workout> result;
    for (int i = 0; i < count && i < static_cast<int>(upcomingWorkouts.size()); ++i) {
        result.push_back(*upcomingWorkouts[i]);
    }
    return result;
}

bool WorkoutPlan::operator==(const WorkoutPlan& other) const {
    return getPlanName() == other.getPlanName();
}

bool WorkoutPlan::operator!=(const WorkoutPlan& other) const {
    return !(*this == other);
}

WorkoutPlan WorkoutPlan::operator+(const WorkoutPlan& other) const {
    WorkoutPlan combined(getPlanName() + " & " + other.getPlanName());
    combined.upcomingWorkouts.reserve(upcomingWorkouts.size() + other.upcomingWorkouts.size());
    combined.upcomingWorkouts.insert(combined.upcomingWorkouts.end(), upcomingWorkouts.begin(), upcomingWorkouts.end());
    combined.upcomingWorkouts.insert(combined.upcomingWorkouts.end(), other.upcomingWorkouts.begin(), other.upcomingWorkouts.end());
    return combined;
}

std::ostream& operator<<(std::ostream& os, const WorkoutPlan& plan) {
    os << "Workout Plan: " << plan.getPlanName() << "\nUpcoming: " << plan.upcomingWorkouts.size();
    return os;
}