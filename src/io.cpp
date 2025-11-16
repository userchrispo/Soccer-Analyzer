#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "io.hpp"
#include "model.hpp"

using namespace std;

// create a safe stoi  and stodincase  they  breaks by being out of range or cant convert to int/double
int safe_stoi(const string &s);
double safe_stod(const string &s);
// load all the matches from the csv file into an vector<Match>
vector<Match> loadMatches(const string &file_location)
{
    ifstream iFile;
    iFile.open(file_location);
    if (!iFile.is_open())
    {
        cout << "Error occured, Could not open file!\n";
        return {};
    }
    vector<Match> matches;

    string line = "";

    getline(iFile, line);

    while (getline(iFile, line))
    {

        vector<string> cols;
        string cells;
        stringstream ss(line);

        while (getline(ss, cells, ','))
        {
            cols.push_back(cells);
        }
        if (cols.size() < 33)
        {
            cout << "Short Line, SKIP" << endl;
            continue;
        }
        Match match;

        match.x = stoi(cols[0]);
        match.season = cols[1];
        match.date = cols[2];
        match.home_team = cols[3];
        match.away_team = cols[4];

        match.home_clearances = safe_stoi(cols[5]);
        match.home_corners = safe_stoi(cols[6]);
        match.home_fouls_conceded = safe_stoi(cols[7]);
        match.home_offsides = safe_stoi(cols[8]);
        match.home_passes = safe_stoi(cols[9]);
        match.home_possession = safe_stod(cols[10]);
        match.home_red_cards = safe_stoi(cols[11]);
        match.home_shots = safe_stoi(cols[12]);
        match.home_shots_on_target = safe_stoi(cols[13]);
        match.home_tackles = safe_stoi(cols[14]);
        match.home_touches = safe_stoi(cols[15]);
        match.home_yellow_cards = safe_stoi(cols[16]);

        match.away_clearances = safe_stoi(cols[17]);
        match.away_corners = safe_stoi(cols[18]);
        match.away_fouls_conceded = safe_stoi(cols[19]);
        match.away_offsides = safe_stoi(cols[20]);
        match.away_passes = safe_stoi(cols[21]);
        match.away_possession = safe_stod(cols[22]);
        match.away_red_cards = safe_stoi(cols[23]);
        match.away_shots = safe_stoi(cols[24]);
        match.away_shots_on_target = safe_stoi(cols[25]);
        match.away_tackles = safe_stoi(cols[26]);
        match.away_touches = safe_stoi(cols[27]);
        match.away_yellow_cards = safe_stoi(cols[28]);

        match.home_goals = safe_stoi(cols[29]);
        match.away_goals = safe_stoi(cols[30]);

        matches.push_back(match);
    }

    return matches;
}

int safe_stoi(const string &s)
{
    if (s.empty())
    {
        return 0;
    }
    try
    {
        return stoi(s);
    }
    catch (const invalid_argument &)
    {
        cout << "ERROR occured, could not convert to int" << endl;
        return 0;
    }
    catch (const out_of_range &)
    {

        cout << "ERROR occured, Number is out of Range" << endl;
        return 0;
    }
};

double safe_stod(const string &s)
{
    if (s.empty())
    {
        return 0;
    }
    try
    {
        return stod(s);
    }
    catch (const invalid_argument &)
    {
        cout << "ERROR occured, could not convert to double" << endl;
        return 0;
    }
    catch (const out_of_range &)
    {

        cout << "ERROR occured, Number is out of Range" << endl;
        return 0;
    }
};