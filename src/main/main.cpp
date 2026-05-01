#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "io.hpp"
#include "model.hpp"
#include "stats.hpp"
#include "rankings.hpp"
#include "season.hpp"
#include "report.hpp"

int main()
{
    vector<Match> matches = loadMatches("data/football_matches.csv");
    vector<Season> seasons = buildSeasons(matches);
    writeAnalysisReport("reports/analysis.txt", matches, seasons);

    unordered_map<string, TeamStats> teams = computeTeamStats(matches);
    advancedStats(teams);

    rankAndDisplay(teams);
    cout << endl
         << "---------------------------------------------------------------------------------------------------------------------";
    advancedRank(teams);

    cout << "\nWrote per-season PL-style tables, head-to-head sample, YoY, unbeaten streaks, and defense rankings to reports/analysis.txt\n";
    return 0;
}