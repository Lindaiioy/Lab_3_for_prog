#include "UserProfile.hpp"
#include <sstream>

ProfileBase::ProfileBase(const std::string& type) : profileType(type) {}

ProfileBase::ProfileBase(const ProfileBase& other) : profileType(other.profileType) {}

ProfileBase::~ProfileBase() = default;

std::string ProfileBase::getType() const {
    return profileType;
}

UserProfile::UserProfile() : ProfileBase("User Profile"), age(0), heightCM(0), weightKG(0.0), notificationsEnabled(false), userName(std::make_unique<std::string>("Anonymous")) {}

UserProfile::UserProfile(const std::string& name, int ageVal, int height, double weight, bool notify)
    : ProfileBase("User Profile"), age(ageVal), heightCM(height), weightKG(weight), notificationsEnabled(notify), userName(std::make_unique<std::string>(name)) {}

UserProfile::UserProfile(const UserProfile& other)
    : ProfileBase(other), age(other.age), heightCM(other.heightCM), weightKG(other.weightKG), notificationsEnabled(other.notificationsEnabled), 
      userName(other.userName ? std::make_unique<std::string>(*other.userName) : nullptr),
      favoriteExercise(other.favoriteExercise) {}

UserProfile& UserProfile::operator=(const UserProfile& other) {
    if (this != &other) {
        ProfileBase::operator=(other);
        age = other.age;
        heightCM = other.heightCM;
        weightKG = other.weightKG;
        notificationsEnabled = other.notificationsEnabled;
        if (other.userName) {
            userName = std::make_unique<std::string>(*other.userName);
        } else {
            userName.reset();
        }
        favoriteExercise = other.favoriteExercise;
    }
    return *this;
}

UserProfile::UserProfile(UserProfile&& other) noexcept
    : ProfileBase(std::move(other)), age(other.age), heightCM(other.heightCM), weightKG(other.weightKG), notificationsEnabled(other.notificationsEnabled), 
      userName(std::move(other.userName)),
      favoriteExercise(std::move(other.favoriteExercise)) {
    other.age = 0;
    other.heightCM = 0;
    other.weightKG = 0.0;
    other.notificationsEnabled = false;
}

UserProfile& UserProfile::operator=(UserProfile&& other) noexcept {
    if (this != &other) {
        ProfileBase::operator=(std::move(other));
        age = other.age;
        heightCM = other.heightCM;
        weightKG = other.weightKG;
        notificationsEnabled = other.notificationsEnabled;
        userName = std::move(other.userName);
        favoriteExercise = std::move(other.favoriteExercise);
        other.age = 0;
        other.heightCM = 0;
        other.weightKG = 0.0;
        other.notificationsEnabled = false;
    }
    return *this;
}

UserProfile::~UserProfile() = default;

bool UserProfile::canPerform(const Exercise& ex) const {
    std::string level = ex.getType();
    if (level.find("Beginner") != std::string::npos && age < 18) {
        return false;
    }
    return true;
}

double UserProfile::updateNewWeight(double weight) {
    weightKG = weight;
    std::stringstream ss;
    ss << "Updated weight to " << weightKG << " kg";
    std::string message = ss.str();
    size_t pos = message.find("to");
    if (pos != std::string::npos) {
        message.replace(pos, 2, "at");
    }
    (void)message;
    return weightKG;
}

bool UserProfile::operator==(const UserProfile& other) const {
    return age == other.age && weightKG == other.weightKG;
}

bool UserProfile::operator!=(const UserProfile& other) const {
    return !(*this == other);
}

UserProfile UserProfile::operator+(const UserProfile& other) const {
    std::string combinedName = *userName + " & " + *other.userName;
    int combinedAge = (age + other.age) / 2;
    int combinedHeight = (heightCM + other.heightCM) / 2;
    double combinedWeight = (weightKG + other.weightKG) / 2;
    bool combinedNotify = notificationsEnabled || other.notificationsEnabled;
    return UserProfile(combinedName, combinedAge, combinedHeight, combinedWeight, combinedNotify);
}

std::ostream& operator<<(std::ostream& os, const UserProfile& profile) {
    os << "User: " << *profile.userName << ", Age: " << profile.age << ", Weight: " << profile.weightKG;
    return os;
}