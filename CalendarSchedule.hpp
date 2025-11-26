#ifndef CALENDARSCHEDULE_HPP
#define CALENDARSCHEDULE_HPP

#include <string>
#include <vector>

class Workout;

class CalendarSchedule {
public:
    std::vector<std::string> scheduledSlots;
    std::string reminderPolicy;

    void scheduleWorkout(const Workout& workout, const std::string& trainingSlot);
    void snoozeList(const std::string& list, int minutes);
    int syncWithSystemCalendar();

    CalendarSchedule();
    ~CalendarSchedule();
};

#endif