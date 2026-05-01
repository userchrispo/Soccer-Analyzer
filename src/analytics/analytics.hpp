#pragma once
#include <string>
#include <vector>
#include "model.hpp"
#include "season.hpp"

struct HeadToHeadRecord
{
    int a_wins = 0;
    int draws = 0;
    int b_wins = 0;
    int a_goals = 0;
    int b_goals = 0;
};

HeadToHeadRecord headToHead(const std::vector<Match> &matches, const std::string &teamA, const std::string &teamB);

struct UnbeatenStreak
{
    std::string season;
    std::string team;
    int length = 0;
    std::string from_date;
    std::string to_date;
};

/** Longest unbeaten run (W or D) within each season, chronologically by match date. */
UnbeatenStreak longestUnbeatenInSeason(const Season &season);

struct YoYRow
{
    std::string team;
    std::string from_season;
    std::string to_season;
    int from_points = 0;
    int to_points = 0;
    int points_delta = 0;
    int from_rank = 0;
    int to_rank = 0;
    int rank_delta = 0; // positive = moved up (lower rank number)
};

std::vector<YoYRow> yearOverYearDeltas(const std::vector<Season> &seasons);

struct DefenseRow
{
    std::string team;
    int gp = 0;
    int ga = 0;
    double ga_per_game = 0;
};

std::vector<DefenseRow> bestDefense(const Season &season, std::size_t topN = 5);
