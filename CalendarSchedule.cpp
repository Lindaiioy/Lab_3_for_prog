#include "CalendarSchedule.hpp"
#include <algorithm>
#include <sstream>

ScheduleBase::ScheduleBase(const std::string& owner) : ownerName(owner) {}

ScheduleBase::ScheduleBase(const ScheduleBase& other) : ownerName(other.ownerName) {}

ScheduleBase::~ScheduleBase() = default;

std::string ScheduleBase::getOwnerName() const {
    return ownerName;
}

CalendarSchedule::CalendarSchedule() : ScheduleBase("Default User"), currentWorkout(nullptr) {
}

CalendarSchedule::CalendarSchedule(const std::string& owner)
    : ScheduleBase(owner), currentWorkout(nullptr) {}

CalendarSchedule::CalendarSchedule(const CalendarSchedule& other)
    : ScheduleBase(other),  
      currentWorkout(other.currentWorkout ? 
                     std::make_unique<Workout>(*other.currentWorkout) : nullptr)
{
    schedule = other.schedule;
    snoozedWorkouts = other.snoozedWorkouts;
}

CalendarSchedule& CalendarSchedule::operator=(const CalendarSchedule& other) {
    if (this != &other) {
        ScheduleBase::operator=(other);  

        if (other.currentWorkout) {
            currentWorkout = std::make_unique<Workout>(*other.currentWorkout);
        } else {
            currentWorkout.reset();
        }

        schedule = other.schedule;
        snoozedWorkouts = other.snoozedWorkouts;
    }
    return *this;
}

CalendarSchedule::CalendarSchedule(CalendarSchedule&& other) noexcept
    : ScheduleBase(std::move(other)),
      currentWorkout(std::move(other.currentWorkout)),
      schedule(std::move(other.schedule)),
      snoozedWorkouts(std::move(other.snoozedWorkouts))
{
}

CalendarSchedule& CalendarSchedule::operator=(CalendarSchedule&& other) noexcept {
    if (this != &other) {
        ScheduleBase::operator=(std::move(other));
        currentWorkout = std::move(other.currentWorkout);
        schedule = std::move(other.schedule);
        snoozedWorkouts = std::move(other.snoozedWorkouts);
    }
    return *this;
}

CalendarSchedule::~CalendarSchedule() = default;

void CalendarSchedule::scheduleWorkout(const Workout& workout, const std::string& trainingSlot) {
    auto sharedWorkout = std::make_shared<Workout>(workout);
    schedule[trainingSlot] = sharedWorkout;
    currentWorkout = std::make_unique<Workout>(workout);  
}

void CalendarSchedule::snoozeWorkout(const std::string& trainingSlot, int minutes) {
    auto it = schedule.find(trainingSlot);
    if (it != schedule.end()) {
        snoozedWorkouts.push_back(it->second);  
        schedule.erase(it);

        std::stringstream ss;
        ss << "Workout snoozed for " << minutes << " minutes.";
        std::string message = ss.str();
        (void)message;  
    }
}

int CalendarSchedule::syncWithSystemCalendar() {
    std::string syncStatus = "Sync completed: " + std::to_string(schedule.size()) + " workouts.";
    size_t pos = syncStatus.find("completed");
    return pos != std::string::npos ? static_cast<int>(schedule.size()) : -1;
}

std::shared_ptr<Workout> CalendarSchedule::operator[](const std::string& slot) const {
    auto it = schedule.find(slot);
    return it != schedule.end() ? it->second : nullptr;
}

bool CalendarSchedule::operator==(const CalendarSchedule& other) const {
    return schedule == other.schedule && 
           getOwnerName() == other.getOwnerName();
}

bool CalendarSchedule::operator!=(const CalendarSchedule& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const CalendarSchedule& cal) {
    os << "Calendar of " << cal.getOwnerName() << "\n";
    os << "Scheduled workouts: " << cal.schedule.size() << "\n";
    for (const auto& [slot, workout] : cal.schedule) {
        os << "  [" << slot << "] " << *workout << "\n";  
    }
    os << "Snoozed: " << cal.snoozedWorkouts.size() << "\n";
    return os;
}