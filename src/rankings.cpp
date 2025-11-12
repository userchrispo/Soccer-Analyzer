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
    cout << string(85, '-') << endl;

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