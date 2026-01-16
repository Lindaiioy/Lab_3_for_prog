#pragma once

#include <memory>
#include <string>
#include <iostream>
#include "UserProfile.hpp"
#include "ProgressTracker.hpp"
#include "Workout.hpp"

class MascotBase {
protected:
    std::string mascotType;
public:
    MascotBase(const std::string& type = "General");
    MascotBase(const MascotBase& other);
    virtual ~MascotBase();
    std::string getType() const;
};

class Mascot : public MascotBase {
private:
    int xp;
    std::unique_ptr<std::string> name;
    std::shared_ptr<ProgressTracker> tracker;

public:
    Mascot();
    Mascot(const std::string& name, int initialXp);
    
    Mascot(const Mascot& other);
    Mascot& operator=(const Mascot& other);
    
    Mascot(Mascot&& other) noexcept;
    Mascot& operator=(Mascot&& other) noexcept;

    ~Mascot();

    std::string reactToWorkoutStart(const Workout& workoutStatus) const;
    std::string getDailyMessage(const UserProfile& user, const ProgressTracker& progress) const;

    bool operator==(const Mascot& other) const;
    bool operator!=(const Mascot& other) const;
    Mascot operator+(const Mascot& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Mascot& mascot);
};