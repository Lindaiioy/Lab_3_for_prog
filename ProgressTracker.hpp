#include "ProgressTracker.hpp"
#include <sstream>

TrackerBase::TrackerBase(const std::string& type) : trackerType(type) {}

TrackerBase::TrackerBase(const TrackerBase& other) : trackerType(other.trackerType) {}

TrackerBase::~TrackerBase() = default;

std::string TrackerBase::getType() const {
    return trackerType;
}

ProgressTracker::ProgressTracker() : TrackerBase("Progress Tracker"), streak(0), bestStreak(0), achievementRate(std::make_unique<double>(0.0)), lastUpdate(std::make_shared<std::string>("None")) {}

ProgressTracker::ProgressTracker(const std::string& type) : TrackerBase(type), streak(0), bestStreak(0), achievementRate(std::make_unique<double>(0.0)), lastUpdate(std::make_shared<std::string>("None")) {}

ProgressTracker::ProgressTracker(const ProgressTracker& other)
    : TrackerBase(other), streak(other.streak), bestStreak(other.bestStreak), 
      achievementRate(other.achievementRate ? std::make_unique<double>(*other.achievementRate) : nullptr),
      lastUpdate(other.lastUpdate) {}

ProgressTracker& ProgressTracker::operator=(const ProgressTracker& other) {
    if (this != &other) {
        TrackerBase::operator=(other);
        streak = other.streak;
        bestStreak = other.bestStreak;
        if (other.achievementRate) {
            achievementRate = std::make_unique<double>(*other.achievementRate);
        } else {
            achievementRate.reset();
        }
        lastUpdate = other.lastUpdate;
    }
    return *this;
}

ProgressTracker::ProgressTracker(ProgressTracker&& other) noexcept
    : TrackerBase(std::move(other)), streak(other.streak), bestStreak(other.bestStreak), 
      achievementRate(std::move(other.achievementRate)),
      lastUpdate(std::move(other.lastUpdate)) {
    other.streak = 0;
    other.bestStreak = 0;
}

ProgressTracker& ProgressTracker::operator=(ProgressTracker&& other) noexcept {
    if (this != &other) {
        TrackerBase::operator=(std::move(other));
        streak = other.streak;
        bestStreak = other.bestStreak;
        achievementRate = std::move(other.achievementRate);
        lastUpdate = std::move(other.lastUpdate);
        other.streak = 0;
        other.bestStreak = 0;
    }
    return *this;
}

ProgressTracker::~ProgressTracker() = default;

double ProgressTracker::getAchievementPercent(const std::string& dateInterval) const {
    std::string intervalStr = dateInterval + " interval";
    size_t pos = intervalStr.find("interval");
    if (pos != std::string::npos) {
        intervalStr.replace(pos, 8, "period");
    }
    if (achievementRate) {
        return *achievementRate;
    }
    return 0.0;
}

double ProgressTracker::updateFromWorkout(const std::string& result) {
    streak++;
    if (streak > bestStreak) {
        bestStreak = streak;
    }
    std::stringstream ss;
    ss << "Updated with " << result;
    *lastUpdate = ss.str();
    if (achievementRate) {
        *achievementRate += 1.0;
        return *achievementRate;
    }
    return 0.0;
}

double ProgressTracker::estimateIMAX(const std::string& exerciseId) const {
    std::string estimateStr = "Estimate for " + exerciseId;
    if (achievementRate) {
        return *achievementRate * 10.0;
    }
    return 0.0;
}

bool ProgressTracker::operator==(const ProgressTracker& other) const {
    return streak == other.streak && bestStreak == other.bestStreak;
}

bool ProgressTracker::operator!=(const ProgressTracker& other) const {
    return !(*this == other);
}

ProgressTracker ProgressTracker::operator+(const ProgressTracker& other) const {
    ProgressTracker combined(getType() + " & " + other.getType());
    combined.streak = streak + other.streak;
    combined.bestStreak = std::max(bestStreak, other.bestStreak);
    if (achievementRate && other.achievementRate) {
        combined.achievementRate = std::make_unique<double>(*achievementRate + *other.achievementRate);
    }
    combined.lastUpdate = std::make_shared<std::string>(*lastUpdate + " + " + *other.lastUpdate);
    return combined;
}

std::ostream& operator<<(std::ostream& os, const ProgressTracker& tracker) {
    os << "Progress Tracker: Streak " << tracker.streak << ", Best " << tracker.bestStreak;
    if (tracker.achievementRate) {
        os