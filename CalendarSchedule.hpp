#pragma once

#include <memory>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "Workout.hpp"

class ScheduleBase {
protected:
    std::string ownerName;
public:
    ScheduleBase(const std::string& owner = "User");
    ScheduleBase(const ScheduleBase& other);
    virtual ~ScheduleBase();
    std::string getOwnerName() const;
};

class CalendarSchedule : public ScheduleBase {
private:
    std::unique_ptr<Workout> currentWorkout;

    std::map<std::string, std::shared_ptr<Workout>> schedule;

    std::vector<std::shared_ptr<Workout>> snoozedWorkouts;

public:
    CalendarSchedule();
    CalendarSchedule(const std::string& owner);
    
    CalendarSchedule(const CalendarSchedule& other);
    CalendarSchedule& operator=(const CalendarSchedule& other);
    
    CalendarSchedule(CalendarSchedule&& other) noexcept;
    CalendarSchedule& operator=(CalendarSchedule&& other) noexcept;

    ~CalendarSchedule();

    void scheduleWorkout(const Workout& workout, const std::string& trainingSlot);
    void snoozeWorkout(const std::string& trainingSlot, int minutes);
    int syncWithSystemCalendar();

    std::shared_ptr<Workout> operator[](const std::string& slot) const;
    bool operator==(const CalendarSchedule& other) const;
    bool operator!=(const CalendarSchedule& other) const;

    friend std::ostream& operator<<(std::ostream& os, const CalendarSchedule& cal);
};