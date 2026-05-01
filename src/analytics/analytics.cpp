#include "analytics.hpp"
#include <algorithm>
#include <unordered_map>

using namespace std;

HeadToHeadRecord headToHead(const vector<Match> &matches, const string &teamA, const string &teamB)
{
    HeadToHeadRecord r;
    for (const Match &m : matches)
    {
        bool ab = (m.home_team == teamA && m.away_team == teamB);
        bool ba = (m.home_team == teamB && m.away_team == teamA);
        if (!ab && !ba)
            continue;
        int hg = m.home_goals;
        int ag = m.away_goals;
        if (ab)
        {
            r.a_goals += hg;
            r.b_goals += ag;
            if (hg > ag)
                r.a_wins++;
            else if (hg < ag)
                r.b_wins++;
            else
                r.draws++;
        }
        else
        {
            r.a_goals += ag;
            r.b_goals += hg;
            if (ag > hg)
                r.a_wins++;
            else if (ag < hg)
                r.b_wins++;
            else
                r.draws++;
        }
    }
    return r;
}

static vector<Match> sortedByDate(const vector<Match> &ms)
{
    vector<Match> out = ms;
    sort(out.begin(), out.end(), [](const Match &a, const Match &b) {
        if (a.date != b.date)
            return a.date < b.date;
        return a.x < b.x;
    });
    return out;
}

/** Outcome for `team`: 1 win, 0 draw, -1 loss. */
static int resultForTeam(const Match &m, const string &team)
{
    if (m.home_team == team)
    {
        if (m.home_goals > m.away_goals)
            return 1;
        if (m.home_goals == m.away_goals)
            return 0;
        return -1;
    }
    if (m.away_team == team)
    {
        if (m.away_goals > m.home_goals)
            return 1;
        if (m.away_goals == m.home_goals)
            return 0;
        return -1;
    }
    return 0;
}

static vector<const Match *> matchesForTeamChrono(const Season &season, const string &team)
{
    vector<const Match *> out;
    vector<Match> ord = sortedByDate(season.matches);
    for (const Match &m : ord)
    {
        if (m.home_team == team || m.away_team == team)
            out.push_back(&m);
    }
    return out;
}

UnbeatenStreak longestUnbeatenInSeason(const Season &season)
{
    UnbeatenStreak best;
    best.season = season.label;
    best.length = -1;
    unordered_map<string, TeamStats> tab = season.aggregateTable();
    for (const auto &kv : tab)
    {
        const string &team = kv.first;
        vector<const Match *> ms = matchesForTeamChrono(season, team);
        int run = 0;
        string from, to;
        int bestRun = 0;
        string bestFrom, bestTo;
        for (const Match *mp : ms)
        {
            int res = resultForTeam(*mp, team);
            bool unbeaten = (res >= 0);
            if (unbeaten)
            {
                if (run == 0)
                    from = mp->date;
                run++;
                to = mp->date;
                if (run > bestRun)
                {
                    bestRun = run;
                    bestFrom = from;
                    bestTo = to;
                }
            }
            else
            {
                run = 0;
            }
        }
        if (bestRun > best.length || (bestRun == best.length && bestRun > 0 && team < best.team))
        {
            best.length = bestRun;
            best.team = team;
            best.from_date = bestFrom;
            best.to_date = bestTo;
        }
    }
    if (best.length < 0)
    {
        best.length = 0;
        best.team.clear();
    }
    return best;
}

static unordered_map<string, int> ranksFromOrdered(const vector<pair<string, TeamStats>> &ord)
{
    unordered_map<string, int> r;
    for (size_t i = 0; i < ord.size(); ++i)
        r[ord[i].first] = static_cast<int>(i) + 1;
    return r;
}

vector<YoYRow> yearOverYearDeltas(const vector<Season> &seasons)
{
    vector<YoYRow> out;
    if (seasons.size() < 2)
        return out;
    for (size_t i = 0; i + 1 < seasons.size(); ++i)
    {
        const Season &s0 = seasons[i];
        const Season &s1 = seasons[i + 1];
        auto o0 = s0.orderedStandings();
        auto o1 = s1.orderedStandings();
        auto rank0 = ranksFromOrdered(o0);
        auto rank1 = ranksFromOrdered(o1);
        unordered_map<string, TeamStats> t0 = s0.aggregateTable();
        unordered_map<string, TeamStats> t1 = s1.aggregateTable();
        for (const auto &kv : t0)
        {
            const string &name = kv.first;
            if (!t1.count(name))
                continue;
            YoYRow row;
            row.team = name;
            row.from_season = s0.label;
            row.to_season = s1.label;
            row.from_points = kv.second.points;
            row.to_points = t1[name].points;
            row.points_delta = row.to_points - row.from_points;
            row.from_rank = rank0[name];
            row.to_rank = rank1[name];
            row.rank_delta = row.from_rank - row.to_rank;
            out.push_back(row);
        }
    }
    return out;
}

vector<DefenseRow> bestDefense(const Season &season, size_t topN)
{
    auto tab = season.aggregateTable();
    vector<DefenseRow> rows;
    rows.reserve(tab.size());
    for (const auto &kv : tab)
    {
        DefenseRow d;
        d.team = kv.first;
        d.gp = kv.second.games_played;
        d.ga = kv.second.ga;
        d.ga_per_game = d.gp ? static_cast<double>(d.ga) / d.gp : 0;
        rows.push_back(d);
    }
    sort(rows.begin(), rows.end(), [](const DefenseRow &a, const DefenseRow &b) {
        if (a.ga != b.ga)
            return a.ga < b.ga;
        if (a.ga_per_game != b.ga_per_game)
            return a.ga_per_game < b.ga_per_game;
        return a.team < b.team;
    });
    if (rows.size() > topN)
        rows.resize(topN);
    return rows;
}
