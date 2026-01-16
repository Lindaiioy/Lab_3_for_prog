#ifndef LEADERBOARD_HPP
#define LEADERBOARD_HPP

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

class Leaderboard {
public:
    std::string id;
    std::string period;
    std::vector<std::pair<std::string, int>> scores;

    Leaderboard(const Leaderboard& other) = delete;
    Leaderboard& operator=(const Leaderboard& other) = delete;

    Leaderboard(Leaderboard&& other) noexcept = default;
    Leaderboard& operator=(Leaderboard&& other) noexcept = default;

    virtual ~Leaderboard() = default;

    static int totalLeaderboards;

    Leaderboard();
    Leaderboard(const std::string& id_, const std::string& period_);

    static Leaderboard createLeaderboard(const std::string& id_, const std::string& period_);
    void addScore(const std::string& userId, int points);
    std::vector<std::pair<std::string, int>> top(size_t n) const;
    void showLeaderboard() const;

    static int GetTotalLeaderboards();

    Leaderboard& operator+=(const std::pair<std::string, int>& p);
    std::pair<std::string, int> operator[](size_t idx) const;
};

#endif