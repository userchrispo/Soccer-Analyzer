#pragma omce
#include <iostream>
#include <vector>
#include <map>
#include "io.hpp"
#include "model.hpp"

unordered_map<string, TeamStats> computeTeamStats(const vector<Match> &matches)
{

    unordered_map<string, TeamStats> teams;

    for (const auto &m : matches)
    {
        teams[m.home_team].recordResult(m.home_goals, m.away_goals);
        teams[m.away_team].recordResult(m.away_goals, m.home_goals);
    }

    return teams;
}