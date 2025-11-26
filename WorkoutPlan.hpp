#ifndef WORKOUTPLAN_HPP
#define WORKOUTPLAN_HPP

#include <string>
#include <vector>

class UserProfile;
class Workout;
class ExerciseCategory;

class WorkoutPlan {
public:
    std::string id;
    std::string periodStart;
    std::string periodEnd;
    std::vector<Workout> workouts;
    std::string templateType;
    UserProfile* userProfile;

    void generatePersonalizedParams(const ExerciseCategory& category);
    void adaptOnFeedback(const std::string& feedback);
    std::vector<Workout> getUpcoming(int count);

    WorkoutPlan();
    ~WorkoutPlan();
};

#endif