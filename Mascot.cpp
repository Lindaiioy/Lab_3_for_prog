#include "Mascot.hpp"
#include <sstream>

MascotBase::MascotBase(const std::string& type) : mascotType(type) {}

MascotBase::MascotBase(const MascotBase& other) : mascotType(other.mascotType) {}

MascotBase::~MascotBase() = default;

std::string MascotBase::getType() const {
    return mascotType;
}

Mascot::Mascot() : MascotBase("Mascot"), xp(0), name(std::make_unique<std::string>("Default Mascot")) {}

Mascot::Mascot(const std::string& nameStr, int initialXp)
    : MascotBase("Mascot"), xp(initialXp), name(std::make_unique<std::string>(nameStr)) {}

Mascot::Mascot(const Mascot& other)
    : MascotBase(other), xp(other.xp), 
      name(other.name ? std::make_unique<std::string>(*other.name) : nullptr),
      tracker(other.tracker) {}

Mascot& Mascot::operator=(const Mascot& other) {
    if (this != &other) {
        MascotBase::operator=(other);
        xp = other.xp;
        if (other.name) {
            name = std::make_unique<std::string>(*other.name);
        } else {
            name.reset();
        }
        tracker = other.tracker;
    }
    return *this;
}

Mascot::Mascot(Mascot&& other) noexcept
    : MascotBase(std::move(other)), xp(other.xp), name(std::move(other.name)), 
      tracker(std::move(other.tracker)) {
    other.xp = 0;
}

Mascot& Mascot::operator=(Mascot&& other) noexcept {
    if (this != &other) {
        MascotBase::operator=(std::move(other));
        xp = other.xp;
        name = std::move(other.name);
        tracker = std::move(other.tracker);
        other.xp = 0;
    }
    return *this;
}

Mascot::~Mascot() = default;

std::string Mascot::reactToWorkoutStart(const Workout& workoutStatus) const {
    std::string message = "Let's go with " + workoutStatus.getName() + "!";
    size_t pos = message.find("go");
    if (pos != std::string::npos) {
        message.replace(pos, 2, "start");
    }
    return message;
}

std::string Mascot::getDailyMessage(const UserProfile& user, const ProgressTracker& progress) const {
    std::stringstream ss;
    ss << "Good morning, " << user.getProfileInfo() << "! Progress: " << progress.getProgress();
    std::string daily = ss.str();
    daily += " Keep it up!";
    return daily;
}

bool Mascot::operator==(const Mascot& other) const {
    return xp == other.xp && *name == *other.name;
}

bool Mascot::operator!=(const Mascot& other) const {
    return !(*this == other);
}

Mascot Mascot::operator+(const Mascot& other) const {
    std::string combinedName = *name + " & " + *other.name;
    int combinedXp = xp + other.xp;
    return Mascot(combinedName, combinedXp);
}

std::ostream& operator<<(std::ostream& os, const Mascot& mascot) {
    os << "Mascot: " << *mascot.name << " (XP: " << mascot.xp << ")";
    return os;
}