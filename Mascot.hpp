#ifndef MASCOT_HPP
#define MASCOT_HPP

#include <string>
#include <set>
#include <vector>

class UserProfile;
class ProgressTracker;
class Workout;

class Mascot {
public:
    std::string userid;
    std::string name;
    int xp;
    std::set<std::string> skinsOwned;
    std::string reactToWorkoutStart(const Workout& workoutStatus);
    std::string getDailyMessage(const UserProfile& user, const ProgressTracker& progress);

    Mascot();
    ~Mascot();
};

#endif