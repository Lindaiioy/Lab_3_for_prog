#ifndef PROGRESSTRACKER_HPP
#define PROGRESSTRACKER_HPP

#include <string>
#include <vector>

class WorkoutRecord;

class ProgressTracker {
public:
    std::string userid;
    int streak;
    int bestStreak;
    std::vector<std::string> recentRecords;
    double getAchievementPercent(const std::string& dateInterval);
    double updateFromWorkout(const std::string& result);
    double estimateIMAX(const std::string& exerciseId);

    ProgressTracker();
    ~ProgressTracker();
};

#endif