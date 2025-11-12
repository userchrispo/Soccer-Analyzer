#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "io.hpp"
#include "model.hpp"

using namespace std;

// create a safe stoi incase stoi(s) breaks by being out of range or cant convert to int
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
        int x;
        string date;
        string season;
        string home_team;
        string away_team;
        int home_goals;
        int away_goals;
        string tempString;
        
        vector<string> cols;
        string cells;
        stringstream ss(line);

        while (getline(ss, cells, ','))
        {
            cols.push_back(cells);
        }
        if (cols.size() <= 29)
        {
            cout << "Short Line, SKIP" << endl;
            continue;
        }

        x = stoi(cols[0]);
        season = cols[1];
        date = cols[2];
        home_team = cols[3];
        away_team = cols[4];
        home_goals = safe_stoi(cols[28]);
        away_goals = safe_stoi(cols[29]);

        Match match(x, date, season, home_team, away_team, home_goals, away_goals);

        matches.push_back(match);
    }

    return matches;
}

int main()
{

    vector<Match> matches = loadMatches("../data/football_matches.csv");
    cout << matches.size() << endl;

    return 0;
}