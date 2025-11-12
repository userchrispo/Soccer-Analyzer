#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include "model.hpp"

// get all team stats from each match n store it in a unordered hash table where we can look up the key value(team name) and find the value(team statsa) on this team
unordered_map<string, TeamStats> computeTeamStats(const vector<Match> &matches);