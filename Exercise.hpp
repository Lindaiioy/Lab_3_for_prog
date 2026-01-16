#pragma once

#include <memory>
#include <string>
#include <set>
#include <iostream>

class ActivityBase {
protected:
    std::string activityType;
public:
    ActivityBase(const std::string& type = "General");
    ActivityBase(const ActivityBase& other);
    virtual ~ActivityBase();
    std::string getType() const;
};

class Exercise : public ActivityBase {
private:
    std::string name;
    std::unique_ptr<std::string> description;
    std::shared_ptr<std::set<std::string>> requiredEquipment;
    std::string difficultyLevel;

public:
    Exercise();
    Exercise(const std::string& name, const std::string& desc, const std::set<std::string>& equip, const std::string& level);
    
    Exercise(const Exercise& other);
    Exercise& operator=(const Exercise& other);
    
    Exercise(Exercise&& other) noexcept;
    Exercise& operator=(Exercise&& other) noexcept;

    ~Exercise();

    Exercise getAlternative(const std::set<std::string>& useEquipment, const std::string& level) const;

    bool operator==(const Exercise& other) const;
    bool operator!=(const Exercise& other) const;
    Exercise operator+(const Exercise& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Exercise& ex);
};