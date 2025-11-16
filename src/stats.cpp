#pragma once
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
        teams[m.home_team].recordResult(m.home_goals, m.away_goals, m.home_clearances, m.home_corners, m.home_fouls_conceded, m.home_offsides, m.home_passes, m.home_shots, m.home_shots_on_target, m.home_tackles, m.home_touches, m.home_red_cards, m.home_yellow_cards, m.home_possession);

        teams[m.away_team].recordResult(m.away_goals, m.home_goals, m.away_clearances, m.away_corners, m.away_fouls_conceded, m.away_offsides, m.away_passes, m.away_shots, m.away_shots_on_target, m.away_tackles, m.away_touches, m.away_red_cards, m.away_yellow_cards, m.away_possession);
    }

    return teams;
}