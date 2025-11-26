#ifndef EXERCISE_HPP
#define EXERCISE_HPP

#include <string>
#include <set>

class Exercise {
public:
    std::string id;
    std::string name;
    std::set<std::string> muscleGroups;
    std::string type;
    std::string difficulty;
    std::string videoDemo;
    std::string description;
    std::set<std::string> preCondition;

    Exercise getAlternative(const std::set<std::string>& useEquipment, const std::string& level);

    Exercise();
    ~Exercise();
};

#endif