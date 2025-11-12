#include <iostream>
#include <string>
#include <unordered_map>
#include "io.hpp"
#include "model.hpp"
#include "stats.hpp"

int main()
{

    vector<Match> matches = loadMatches("data/football_matches.csv");
    unordered_map<string, TeamStats> teams = computeTeamStats(matches);

    // rank and display ufnction needs to be created 

    return 0;
}