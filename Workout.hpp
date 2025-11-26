#ifndef WORKOUT_HPP
#define WORKOUT_HPP

#include <string>

class Workout {
public:
    std::string id;
    std::string date;
    std::string title;
    std::string bible;
    std::string status;
    std::string notes;

    int complete(const std::string& metrics);
    std::string reschedule(const std::string& newDate);
    double estimateCaloriesUsed();

    Workout();
    ~Workout();
};

#endif