#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <unordered_map>
#include "model.hpp"
#include "rankings.hpp"

using namespace std;

void rankAndDisplay(const unordered_map<string, TeamStats> &teams)
{
    // create a vector that will create a pair of team and the teamstats, it will than sort the vector by highest points, gd or gf.

    vector<pair<string, TeamStats>> teamList(teams.begin(), teams.end());

    sort(teamList.begin(), teamList.end(), [](const auto &teamA, const auto &teamB)
         {
            const TeamStats &A = teamA.second;
            const TeamStats &B = teamB.second;

        if (A.points != B.points)
        {
            return A.points > B.points;
        }
        if (A.goalDiff() != B.goalDiff())
        {
            return A.goalDiff() > B.goalDiff();
        }
        return A.gf > B.gf; });

    int rank = 1;
    cout << left << setw(5) << "Pos"
         << setw(28) << "Team"
         << setw(6) << "GP"
         << setw(7) << "Pts"
         << setw(6) << "W"
         << setw(6) << "D"
         << setw(6) << "L"
         << setw(7) << "GF"
         << setw(7) << "GA"
         << setw(7) << "GD" << endl;
    cout << string(92, '-') << endl;

    for (const auto &teamPair : teamList)
    {
        cout << left << setw(5) << rank++
             << setw(28) << teamPair.first
             << setw(6) << teamPair.second.games_played
             << setw(7) << teamPair.second.points
             << setw(6) << teamPair.second.wins
             << setw(6) << teamPair.second.draws
             << setw(6) << teamPair.second.losses
             << setw(7) << teamPair.second.gf
             << setw(7) << teamPair.second.ga
             << setw(7) << teamPair.second.goalDiff()

             << endl;
    }
}

// advanced rankings
void advancedRank(const unordered_map<string, TeamStats> &teams)
{
    vector<pair<string, TeamStats>> teamList(teams.begin(), teams.end());

    sort(teamList.begin(), teamList.end(), [](const auto &teamA, const auto &teamB)
         {
        const TeamStats &A = teamA.second;
        const TeamStats &B = teamB.second;

        if (A.final_score != B.final_score) {
            return A.final_score > B.final_score;
        }
        if (A.xOFF != B.xOFF) {
            return A.xOFF > B.xOFF;
        }
        if (A.tOFF != B.tOFF) {
            return A.tOFF > B.tOFF;
        }
        if (A.xDEF != B.xDEF) {
            return A.xDEF > B.xDEF;
        }
        if (A.tDEF != B.tDEF) {
            return A.tDEF > B.tDEF;
        }
        return teamA.first < teamB.first; });

    const int wPos = 5;
    const int wTeam = 28;
    const int wGP = 6;
    const int wScore = 12;
    const int wMetric = 11;

    cout << "\n";
    cout << left << setw(wPos) << "Pos"
         << setw(wTeam) << "Team"
         << right << setw(wGP) << "GP"
         << setw(wScore) << "Final Score"
         << setw(wMetric) << "xOFF"
         << setw(wMetric) << "tOFF"
         << setw(wMetric) << "xDEF"
         << setw(wMetric) << "tDEF"
         << setw(wMetric) << "Discipline"
         << setw(wMetric) << "Control" << endl;

    cout << string(wPos + wTeam + wGP + wScore + wMetric * 6, '-') << endl;
    cout << fixed << setprecision(2);

    int rank = 1;
    for (const auto &teamPair : teamList)
    {
        cout << left << setw(wPos) << rank++
             << setw(wTeam) << teamPair.first
             << right << setw(wGP) << teamPair.second.games_played
             << setw(wScore) << teamPair.second.final_score
             << setw(wMetric) << teamPair.second.xOFF
             << setw(wMetric) << teamPair.second.tOFF
             << setw(wMetric) << teamPair.second.xDEF
             << setw(wMetric) << teamPair.second.tDEF
             << setw(wMetric) << teamPair.second.discipline_score
             << setw(wMetric) << teamPair.second.control_score
             << endl;
    }
}
