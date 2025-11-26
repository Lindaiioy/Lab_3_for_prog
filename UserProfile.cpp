#include "UserProfile.hpp"
#include "Exercise.hpp"

UserProfile::UserProfile() : age(0), heightCM(0), weightKG(0.0), notificationsEnabled(false) {}

UserProfile::~UserProfile() {}

bool UserProfile::canPerform(const Exercise& ex) {
    return true;
}

double UserProfile::updateNewWeight(double weight) {
    weightKG = weight;
    return weightKG;
}