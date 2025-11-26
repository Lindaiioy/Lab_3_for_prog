#ifndef EXERCISECATEGORY_HPP
#define EXERCISECATEGORY_HPP

#include <string>
#include <vector>
#include <set>

class Exercise;
class UserProfile;

class ExerciseCategory {
public:
    std::vector<Exercise> exercises;
    std::string name;

    std::vector<Exercise> filterByGoal(const std::string& goal, const std::set<std::string>& equipment, const std::string& level);
    std::vector<Exercise> recommendForSlot(const std::string& workoutSlot, const UserProfile& user, const std::string& history);

    ExerciseCategory();
    ~ExerciseCategory();
};

#endif