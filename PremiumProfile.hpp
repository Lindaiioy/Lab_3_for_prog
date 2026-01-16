// PremiumProfile.hpp
#pragma once
#include "CommunityProfile.hpp"
#include <string>

class PremiumProfile : public CommunityProfile {
public:
    std::string subscriptionLevel;

    // ����� ������������ �������� ������ �� ������������ ������������ (feature)
    PremiumProfile(const std::string& id_, const std::string& nick_, const std::string& joined, const std::string& level)
        : CommunityProfile(id_, nick_, joined), subscriptionLevel(level) {
        // �����������: ����� ������������ �������� �������� � ������ �������������
    }

    PremiumProfile(const PremiumProfile& other)
        : CommunityProfile(other), subscriptionLevel(other.subscriptionLevel) {
        // ������������ ������ ������������ �������� � copy ctor
    }

    ~PremiumProfile() = default;

    // ��������������� ������������ ������ (������� � ������� ��������)
    void showProfileInfo() const override {
        // ����� ������� ������� ������� �����, � ����� �������� �������������� ����������
        CommunityProfile::showProfileInfo(); // ����� ����� �������� ������
        std::cout << "  Subscription: " << subscriptionLevel << "\n";
    }

    // ���������� ��������� ������������: ���������� �������� � �����������
    PremiumProfile& operator=(const CommunityProfile& base) {
        // �������� ���� �� �������� ������
        this->id = base.id;
        this->nickname = base.nickname;
        this->joinedDate = base.joinedDate;
        // friends � badges protected � ����� ���������� (feature: protected)

        // note � ������� �������� �����, ���� base.note ����������
        if (this->note) delete this->note;
        this->note = base.note ? new std::string(*(base.note)) : nullptr;
        // subscriptionLevel ��������� ������� (��� �������� ������)
        return *this;
    }
};