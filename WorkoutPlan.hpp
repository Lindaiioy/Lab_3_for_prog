#pragma once

#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include "UserProfile.hpp"
#include "Workout.hpp"
#include "ExerciseCategory.hpp"

class PlanBase {
protected:
    std::string planName;
public:
    PlanBase(const std::string& name = "General");
    PlanBase(const PlanBase& other);
    virtual ~PlanBase();
    std::string getPlanName() const;
};

class WorkoutPlan : public PlanBase {
private:
    std::unique_ptr<UserProfile> userProfile;
    std::vector<std::shared_ptr<Workout>> upcomingWorkouts;

public:
    WorkoutPlan();
    WorkoutPlan(const std::string& name);
    
    WorkoutPlan(const WorkoutPlan& other);
    WorkoutPlan& operator=(const WorkoutPlan& other);
    
    WorkoutPlan(WorkoutPlan&& other) noexcept;
    WorkoutPlan& operator=(WorkoutPlan&& other) noexcept;

    ~WorkoutPlan();

    void generatePersonalizedParams(const ExerciseCategory& category);
    void adaptOnFeedback(const std::string& feedback);
    std::vector<Workout> getUpcoming(int count) const;

    bool operator==(const WorkoutPlan& other) const;
    bool operator!=(const WorkoutPlan& other) const;
    WorkoutPlan operator+(const WorkoutPlan& other) const;

    friend std::ostream& operator<<(std::ostream& os, const WorkoutPlan& plan);
};