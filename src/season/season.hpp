#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "model.hpp"

struct Season
{
    std::string label;
    std::vector<Match> matches;

    std::unordered_map<std::string, TeamStats> aggregateTable() const;
    /** Premier League-style: points, goal difference, goals scored, then head-to-head among tied clubs (mini-league), then away goals in mutual fixtures when only two clubs remain tied. */
    std::vector<std::pair<std::string, TeamStats>> orderedStandings() const;
};

std::vector<Season> buildSeasons(const std::vector<Match> &all);
