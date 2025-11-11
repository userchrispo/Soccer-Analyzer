#pragma omce
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include "model.hpp"

// get all team stats from each match
unordered_map<string, TeamStats> computeTeamStats(const vector<Match> &matches);