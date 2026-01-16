#include "Exercise.hpp"
#include <algorithm>
#include <sstream>

ActivityBase::ActivityBase(const std::string& type) : activityType(type) {}

ActivityBase::ActivityBase(const ActivityBase& other) : activityType(other.activityType) {}

ActivityBase::~ActivityBase() = default;

std::string ActivityBase::getType() const {
    return activityType;
}

Exercise::Exercise() : ActivityBase("Exercise"), name("Default"), description(std::make_unique<std::string>("No description")), requiredEquipment(std::make_shared<std::set<std::string>>()), difficultyLevel("Beginner") {}

Exercise::Exercise(const std::string& name, const std::string& desc, const std::set<std::string>& equip, const std::string& level)
    : ActivityBase("Exercise"), name(name), description(std::make_unique<std::string>(desc)), requiredEquipment(std::make_shared<std::set<std::string>>(equip)), difficultyLevel(level) {}

Exercise::Exercise(const Exercise& other)
    : ActivityBase(other), name(other.name), description(other.description ? std::make_unique<std::string>(*other.description) : nullptr), 
      requiredEquipment(other.requiredEquipment), difficultyLevel(other.difficultyLevel) {}

Exercise& Exercise::operator=(const Exercise& other) {
    if (this != &other) {
        ActivityBase::operator=(other);
        name = other.name;
        if (other.description) {
            description = std::make_unique<std::string>(*other.description);
        } else {
            description.reset();
        }
        requiredEquipment = other.requiredEquipment;
        difficultyLevel = other.difficultyLevel;
    }
    return *this;
}

Exercise::Exercise(Exercise&& other) noexcept
    : ActivityBase(std::move(other)), name(std::move(other.name)), description(std::move(other.description)), 
      requiredEquipment(std::move(other.requiredEquipment)), difficultyLevel(std::move(other.difficultyLevel)) {}

Exercise& Exercise::operator=(Exercise&& other) noexcept {
    if (this != &other) {
        ActivityBase::operator=(std::move(other));
        name = std::move(other.name);
        description = std::move(other.description);
        requiredEquipment = std::move(other.requiredEquipment);
        difficultyLevel = std::move(other.difficultyLevel);
    }
    return *this;
}

Exercise::~Exercise() = default;

Exercise Exercise::getAlternative(const std::set<std::string>& useEquipment, const std::string& level) const {
    Exercise alt = *this;
    alt.requiredEquipment = std::make_shared<std::set<std::string>>(useEquipment);
    alt.difficultyLevel = level;

    std::string newDesc = "Alternative: " + *description;
    size_t pos = newDesc.find("No");
    if (pos != std::string::npos) {
        newDesc.replace(pos, 2, "Yes");
    }
    alt.description = std::make_unique<std::string>(newDesc);

    std::stringstream ss;
    ss << "Level: " << level;
    alt.name += ss.str();

    return alt;
}

bool Exercise::operator==(const Exercise& other) const {
    return name == other.name && difficultyLevel == other.difficultyLevel;
}

bool Exercise::operator!=(const Exercise& other) const {
    return !(*this == other);
}

Exercise Exercise::operator+(const Exercise& other) const {
    std::set<std::string> combinedEquip;
    std::set_union(requiredEquipment->begin(), requiredEquipment->end(),
                   other.requiredEquipment->begin(), other.requiredEquipment->end(),
                   std::inserter(combinedEquip, combinedEquip.begin()));

    std::string combinedDesc = *description + " + " + *other.description;
    std::string combinedName = name + " & " + other.name;
    std::string combinedLevel = difficultyLevel + "/" + other.difficultyLevel;

    return Exercise(combinedName, combinedDesc, combinedEquip, combinedLevel);
}

std::ostream& operator<<(std::ostream& os, const Exercise& ex) {
    os << "Exercise: " << ex.name << " (" << ex.difficultyLevel << ")";
    if (ex.description) {
        os << " - " << *ex.description;
    }
    os << "\nEquipment: ";
    for (const auto& eq : *ex.requiredEquipment) {
        os << eq << " ";
    }
    return os;
}