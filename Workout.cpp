#include "Workout.hpp"

Workout::Workout() {}

Workout::~Workout() {}

int Workout::complete(const std::string& metrics) {
    return 0;
}

std::string Workout::reschedule(const std::string& newDate) {
    date = newDate;
    return date;
}

double Workout::estimateCaloriesUsed() {
    return 0.0;
}