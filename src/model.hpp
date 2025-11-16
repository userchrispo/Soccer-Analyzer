#pragma once
#include <iostream>
using namespace std;

// create match struct to hold each matches data
struct Match
{
    int x = 0;
    string date;
    string season;
    string home_team;
    string away_team;
    int home_clearances = 0;
    int home_corners = 0;
    int home_fouls_conceded = 0;
    int home_offsides = 0;
    int home_passes = 0;
    double home_possession = 0;
    int home_red_cards = 0;
    int home_shots = 0;
    int home_shots_on_target = 0;
    int home_tackles = 0;
    int home_touches = 0;
    int home_yellow_cards = 0;

    int away_clearances = 0;
    int away_corners = 0;
    int away_fouls_conceded = 0;
    int away_offsides = 0;
    int away_passes = 0;
    double away_possession = 0;
    int away_red_cards = 0;
    int away_shots = 0;
    int away_shots_on_target = 0;
    int away_tackles = 0;
    int away_touches = 0;
    int away_yellow_cards = 0;

    int home_goals = 0;
    int away_goals = 0;
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
    int clearances = 0;
    int corners = 0;
    int fouls_conceded = 0;
    int offsides = 0;
    int passes = 0;
    int shots = 0;
    int shots_on_target = 0;
    int tackles = 0;
    int touches = 0;
    int red_cards = 0;
    int yellow_cards = 0;

    double total_possession = 0;

    // use record result so we can update each team, after that create a new function to get simplify stats and calc average. avg poesssion method,
    void recordResult(int goalsFor, int goalsAgainst, int clearances_, int corners_, int fouls_conceded_, int offsides_, int passes_, int shots_, int shots_on_target_, int tackles_, int touches_, int red_cards_, int yellow_cards_, double possession_)
    {
        games_played++;
        clearances += clearances_;
        corners += corners_;
        fouls_conceded += fouls_conceded_;
        offsides += offsides_;
        passes += passes_;
        shots += shots_;
        shots_on_target += shots_on_target_;
        tackles += tackles_;
        touches += touches_;
        red_cards += red_cards_;
        yellow_cards += yellow_cards_;
        total_possession += possession_;

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
    }
    int goalDiff() const { return gf - ga; }

    // get average  underlying stats for team
    double avgClearances() const { return games_played ? ((double)clearances / games_played) : 0; }

    double avgCorners() const { return games_played ? ((double)corners / games_played) : 0; }

    double avgFoulsConceded() const { return games_played ? ((double)fouls_conceded / games_played) : 0; }

    double avgOffsides() const { return games_played ? ((double)offsides / games_played) : 0; }

    double avgPasses() const { return games_played ? ((double)passes / games_played) : 0; }

    double avgShots() const { return games_played ? ((double)shots / games_played) : 0; }

    double avgShotsOnTarget() const { return games_played ? ((double)shots_on_target / games_played) : 0; }

    double avgTackles() const { return games_played ? ((double)tackles / games_played) : 0; }

    double avgTouches() const { return games_played ? ((double)touches / games_played) : 0; }

    double avgRedCards() const { return games_played ? ((double)red_cards / games_played) : 0; }

    double avgYellowCards() const { return games_played ? ((double)yellow_cards / games_played) : 0; }

    double avgPossession() const { return games_played ? ((double)total_possession / games_played) : 0; }
};