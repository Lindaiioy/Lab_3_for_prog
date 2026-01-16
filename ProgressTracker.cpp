#pragma once

#include <memory>
#include <string>
#include <iostream>

class TrackerBase {
protected:
    std::string trackerType;
public:
    TrackerBase(const std::string& type = "General");
    TrackerBase(const TrackerBase& other);
    virtual ~TrackerBase();
    std::string getType() const;
};

class ProgressTracker : public TrackerBase {
private:
    int streak;
    int bestStreak;
    std::unique_ptr<double> achievementRate;
    std::shared_ptr<std::string> lastUpdate;

public:
    ProgressTracker();
    ProgressTracker(const std::string& type);
    
    ProgressTracker(const ProgressTracker& other);
    ProgressTracker& operator=(const ProgressTracker& other);
    
    ProgressTracker(ProgressTracker&& other) noexcept;
    ProgressTracker& operator=(ProgressTracker&& other) noexcept;

    ~ProgressTracker();

    double getAchievementPercent(const std::string& dateInterval) const;
    double updateFromWorkout(const std::string& result);
    double estimateIMAX(const std::string& exerciseId) const;

    bool operator==(const ProgressTracker& other) const;
    bool operator!=(const ProgressTracker& other) const;
    ProgressTracker operator+(const ProgressTracker& other) const;

    friend std::ostream& operator<<(std::ostream& os, const ProgressTracker& tracker);
};