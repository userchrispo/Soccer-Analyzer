#pragma once
#include <iostream>
using namespace std;

// create match struct to hold each matches data
struct Match
{
    string x;
    string date;
    string season;
    string home_team;
    string away_team;
    int home_goals = 0;
    int away_goals = 0;

    Match(int x, const string &date, const string &season, const string &home_team, const string &away_team, int home_goals, int away_goals)
    {
        this->x = x;
        this->date = date;
        this->season = season;
        this->home_team = home_team;
        this->away_team = away_team;
        this->home_goals = home_goals;
        this->away_goals = away_goals;
    }
};

// create teamStats struct to hold each specific teams stats.
struct TeamStats
{
    int games_played = 0;
    int points = 0;
    int gf = 0;
    int ga = 0;
    int wins = 0;
    int losses = 0;
    int draws = 0;

    void recordResult(int goalsFor, int goalsAgainst)
    {
        if (goalsFor > goalsAgainst)
        {
            points += 3;
            wins += 1;
        }
        else if (goalsFor == goalsAgainst)
        {
            points += 1;
            draws += 1;
        }
        else
        {
            losses += 1;
        }

        gf += goalsFor;
        ga += goalsAgainst;
        games_played += 1;
    }
    int goalDiff() const { return gf - ga; }
};