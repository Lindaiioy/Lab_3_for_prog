#pragma once

#include <memory>
#include <string>
#include <iostream>
#include "Exercise.hpp"

class ProfileBase {
protected:
    std::string profileType;
public:
    ProfileBase(const std::string& type = "General");
    ProfileBase(const ProfileBase& other);
    virtual ~ProfileBase();
    std::string getType() const;
};

class UserProfile : public ProfileBase {
private:
    int age;
    int heightCM;
    double weightKG;
    bool notificationsEnabled;
    std::unique_ptr<std::string> userName;
    std::shared_ptr<Exercise> favoriteExercise;

public:
    UserProfile();
    UserProfile(const std::string& name, int ageVal, int height, double weight, bool notify);
    
    UserProfile(const UserProfile& other);
    UserProfile& operator=(const UserProfile& other);
    
    UserProfile(UserProfile&& other) noexcept;
    UserProfile& operator=(UserProfile&& other) noexcept;

    ~UserProfile();

    bool canPerform(const Exercise& ex) const;
    double updateNewWeight(double weight);

    bool operator==(const UserProfile& other) const;
    bool operator!=(const UserProfile& other) const;
    UserProfile operator+(const UserProfile& other) const;

    friend std::ostream& operator<<(std::ostream& os, const UserProfile& profile);
};