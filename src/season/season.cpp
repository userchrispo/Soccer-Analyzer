#include "season.hpp"
#include "stats.hpp"
#include <algorithm>
#include <unordered_set>

using namespace std;

unordered_map<string, TeamStats> Season::aggregateTable() const
{
    return computeTeamStats(matches);
}

static void miniLeagueStats(const vector<Match> &seasonMatches,
                            const unordered_set<string> &names,
                            unordered_map<string, int> &pts,
                            unordered_map<string, int> &gf,
                            unordered_map<string, int> &ga)
{
    pts.clear();
    gf.clear();
    ga.clear();
    for (const string &n : names)
    {
        pts[n] = 0;
        gf[n] = 0;
        ga[n] = 0;
    }
    for (const Match &m : seasonMatches)
    {
        if (!names.count(m.home_team) || !names.count(m.away_team))
            continue;
        int hg = m.home_goals;
        int ag = m.away_goals;
        gf[m.home_team] += hg;
        ga[m.home_team] += ag;
        gf[m.away_team] += ag;
        ga[m.away_team] += hg;
        if (hg > ag)
            pts[m.home_team] += 3;
        else if (hg < ag)
            pts[m.away_team] += 3;
        else
        {
            pts[m.home_team] += 1;
            pts[m.away_team] += 1;
        }
    }
}

static int awayGoalsInMutualFixtures(const vector<Match> &seasonMatches,
                                     const string &scorer,
                                     const string &opponent)
{
    int g = 0;
    for (const Match &m : seasonMatches)
    {
        if (m.home_team == scorer && m.away_team == opponent)
            continue;
        if (m.away_team == scorer && m.home_team == opponent)
            g += m.away_goals;
    }
    return g;
}

static void sortTieGroup(vector<pair<string, TeamStats>> &group, const vector<Match> &seasonMatches)
{
    if (group.size() <= 1)
        return;

    unordered_set<string> names;
    for (const auto &row : group)
        names.insert(row.first);

    unordered_map<string, int> mini_pts, mini_gf, mini_ga;
    miniLeagueStats(seasonMatches, names, mini_pts, mini_gf, mini_ga);

    sort(group.begin(), group.end(), [&](const pair<string, TeamStats> &A, const pair<string, TeamStats> &B) {
        int ap = mini_pts[A.first];
        int bp = mini_pts[B.first];
        if (ap != bp)
            return ap > bp;
        int agd = mini_gf[A.first] - mini_ga[A.first];
        int bgd = mini_gf[B.first] - mini_ga[B.first];
        if (agd != bgd)
            return agd > bgd;
        if (mini_gf[A.first] != mini_gf[B.first])
            return mini_gf[A.first] > mini_gf[B.first];
        if (group.size() == 2)
        {
            int a_aw = awayGoalsInMutualFixtures(seasonMatches, A.first, B.first);
            int b_aw = awayGoalsInMutualFixtures(seasonMatches, B.first, A.first);
            if (a_aw != b_aw)
                return a_aw > b_aw;
        }
        return A.first < B.first;
    });
}

vector<pair<string, TeamStats>> Season::orderedStandings() const
{
    auto raw = aggregateTable();
    vector<pair<string, TeamStats>> rows(raw.begin(), raw.end());
    sort(rows.begin(), rows.end(), [](const auto &a, const auto &b) {
        if (a.second.points != b.second.points)
            return a.second.points > b.second.points;
        if (a.second.goalDiff() != b.second.goalDiff())
            return a.second.goalDiff() > b.second.goalDiff();
        return a.second.gf > b.second.gf;
    });

    size_t i = 0;
    while (i < rows.size())
    {
        size_t j = i + 1;
        while (j < rows.size() && rows[j].second.points == rows[i].second.points &&
               rows[j].second.goalDiff() == rows[i].second.goalDiff() &&
               rows[j].second.gf == rows[i].second.gf)
            ++j;
        if (j - i > 1)
        {
            vector<pair<string, TeamStats>> chunk(rows.begin() + static_cast<long>(i), rows.begin() + static_cast<long>(j));
            sortTieGroup(chunk, matches);
            copy(chunk.begin(), chunk.end(), rows.begin() + static_cast<long>(i));
        }
        i = j;
    }
    return rows;
}

vector<Season> buildSeasons(const vector<Match> &all)
{
    unordered_map<string, vector<Match>> buckets;
    for (const Match &m : all)
        buckets[m.season].push_back(m);

    vector<string> keys;
    keys.reserve(buckets.size());
    for (const auto &p : buckets)
        keys.push_back(p.first);
    sort(keys.begin(), keys.end());

    vector<Season> out;
    out.reserve(keys.size());
    for (const string &k : keys)
        out.push_back(Season{k, std::move(buckets[k])});
    return out;
}
