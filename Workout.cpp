#include "Workout.hpp"
#include <sstream>

WorkoutBase::WorkoutBase(const std::string& type) : workoutType(type) {}

WorkoutBase::WorkoutBase(const WorkoutBase& other) : workoutType(other.workoutType) {}

WorkoutBase::~WorkoutBase() = default;

std::string WorkoutBase::getType() const {
    return workoutType;
}

Workout::Workout() : WorkoutBase("Workout"), date("Today"), metricsData(std::make_unique<std::string>("No metrics")) {}

Workout::Workout(const std::string& dateVal) : WorkoutBase("Workout"), date(dateVal), metricsData(std::make_unique<std::string>("No metrics")) {}

Workout::Workout(const Workout& other)
    : WorkoutBase(other), date(other.date), 
      metricsData(other.metricsData ? std::make_unique<std::string>(*other.metricsData) : nullptr),
      caloriesEstimate(other.caloriesEstimate) {}

Workout& Workout::operator=(const Workout& other) {
    if (this != &other) {
        WorkoutBase::operator=(other);
        date = other.date;
        if (other.metricsData) {
            metricsData = std::make_unique<std::string>(*other.metricsData);
        } else {
            metricsData.reset();
        }
        caloriesEstimate = other.caloriesEstimate;
    }
    return *this;
}

Workout::Workout(Workout&& other) noexcept
    : WorkoutBase(std::move(other)), date(std::move(other.date)), 
      metricsData(std::move(other.metricsData)),
      caloriesEstimate(std::move(other.caloriesEstimate)) {}

Workout& Workout::operator=(Workout&& other) noexcept {
    if (this != &other) {
        WorkoutBase::operator=(std::move(other));
        date = std::move(other.date);
        metricsData = std::move(other.metricsData);
        caloriesEstimate = std::move(other.caloriesEstimate);
    }
    return *this;
}

Workout::~Workout() = default;

int Workout::complete(const std::string& metrics) {
    std::stringstream ss;
    ss << "Completed with " << metrics;
    *metricsData = ss.str();
    size_t pos = metricsData->find("with");
    if (pos != std::string::npos) {
        metricsData->replace(pos, 4, "using");
    }
    return 1;
}

std::string Workout::reschedule(const std::string& newDate) {
    date = newDate;
    std::string message = "Rescheduled to " + date;
    return message;
}

double Workout::estimateCaloriesUsed() const {
    std::string estimateStr = "Estimate: 500";
    if (caloriesEstimate) {
        return *caloriesEstimate;
    }
    return 0.0;
}

bool Workout::operator==(const Workout& other) const {
    return date == other.date;
}

bool Workout::operator!=(const Workout& other) const {
    return !(*this == other);
}

Workout Workout::operator+(const Workout& other) const {
    std::string combinedDate = date + " & " + other.date;
    return Workout(combinedDate);
}

std::ostream& operator<<(std::ostream& os, const Workout& workout) {
    os << "Workout on " << workout.date;
    if (workout.metricsData) {
        os << " - " << *workout.metricsData;
    }
    return os;
}