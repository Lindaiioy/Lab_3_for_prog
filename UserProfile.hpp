#ifndef USERPROFILE_HPP
#define USERPROFILE_HPP

#include <string>
#include <set>

class Exercise;

class UserProfile {
public:
    std::string id;
    std::string name;
    int age;
    int heightCM;
    double weightKG;
    std::string goal;
    std::string level;
    std::set<std::string> equipment;
    bool notificationsEnabled;

    bool canPerform(const Exercise& ex);
    double updateNewWeight(double weight);

    UserProfile();
    ~UserProfile();
};

#endif