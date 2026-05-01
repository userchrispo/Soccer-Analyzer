#pragma once
#include <string>
#include <vector>
#include "model.hpp"
#include "season.hpp"

void writeAnalysisReport(const std::string &path,
                         const std::vector<Match> &matches,
                         const std::vector<Season> &seasons);
