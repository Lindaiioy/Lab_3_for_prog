#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Achievement.hpp"
#include "ProfileBase.hpp"

class CommunityProfile : public ProfileBase {
protected:
    std::vector<std::string> friends;
    std::vector<Achievement> badges;

public:
    std::string id;
    std::string nickname;
    std::string joinedDate;

    std::string* note;

    CommunityProfile();
    CommunityProfile(const std::string& id_, const std::string& nick_, const std::string& joined);
    CommunityProfile(const CommunityProfile& other);
    CommunityProfile& operator=(const CommunityProfile& other);

    virtual ~CommunityProfile();

    static CommunityProfile createProfile(const std::string& id_, const std::string& nick_, const std::string& joined);

    void addFriend(const std::string& friendId);
    void awardBadge(const Achievement& badge);

    void showProfileInfo() const override;

    CommunityProfile operator+(const CommunityProfile& rhs) const;

    ProfileBase* cloneShallow() const override;
    ProfileBase* cloneDeep() const override;

    friend std::ostream& operator<<(std::ostream& os, const CommunityProfile& p);
};