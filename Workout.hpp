#pragma once

#include <memory>
#include <string>
#include <iostream>

class WorkoutBase {
protected:
    std::string workoutType;
public:
    WorkoutBase(const std::string& type = "General");
    WorkoutBase(const WorkoutBase& other);
    virtual ~WorkoutBase();
    std::string getType() const;
};

class Workout : public WorkoutBase {
private:
    std::string date;
    std::unique_ptr<std::string> metricsData;
    std::shared_ptr<double> caloriesEstimate;

public:
    Workout();
    Workout(const std::string& dateVal);
    
    Workout(const Workout& other);
    Workout& operator=(const Workout& other);
    
    Workout(Workout&& other) noexcept;
    Workout& operator=(Workout&& other) noexcept;

    ~Workout();

    int complete(const std::string& metrics);
    std::string reschedule(const std::string& newDate);
    double estimateCaloriesUsed() const;

    bool operator==(const Workout& other) const;
    bool operator!=(const Workout& other) const;
    Workout operator+(const Workout& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Workout& workout);
};