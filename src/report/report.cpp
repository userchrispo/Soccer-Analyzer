#include "report.hpp"
#include "analytics.hpp"
#include <fstream>
#include <iomanip>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

static void writeSeasonTable(ostream &o, const Season &s)
{
    auto ord = s.orderedStandings();
    o << "Season " << s.label << " — PL-style order (Pts, GD, GF, head-to-head)\n";
    o << left << setw(4) << "#" << setw(28) << "Team" << right << setw(5) << "GP" << setw(5) << "Pts"
      << setw(5) << "W" << setw(5) << "D" << setw(5) << "L" << setw(6) << "GF" << setw(6) << "GA" << setw(6) << "GD"
      << "\n";
    int pos = 1;
    for (const auto &row : ord)
    {
        const TeamStats &t = row.second;
        o << left << setw(4) << pos++ << setw(28) << row.first << right << setw(5) << t.games_played
          << setw(5) << t.points << setw(5) << t.wins << setw(5) << t.draws << setw(5) << t.losses
          << setw(6) << t.gf << setw(6) << t.ga << setw(6) << t.goalDiff() << "\n";
    }
    o << "\n";
}

void writeAnalysisReport(const string &path, const vector<Match> &matches, const vector<Season> &seasons)
{
    fs::path fp(path);
    if (fp.has_parent_path())
        fs::create_directories(fp.parent_path());
    ofstream out(path);
    if (!out)
        return;

    out << "Soccer analyzer — report\n";
    out << "Matches: " << matches.size() << "  Seasons: " << seasons.size() << "\n\n";

    for (const Season &s : seasons)
        writeSeasonTable(out, s);

    out << "=== Example head-to-head (all seasons in file) ===\n";
    auto h = headToHead(matches, "Liverpool", "Manchester United");
    out << "Liverpool vs Manchester United — A wins: " << h.a_wins << "  draws: " << h.draws
        << "  B wins: " << h.b_wins << "  goals A: " << h.a_goals << "  goals B: " << h.b_goals << "\n\n";

    out << "=== Longest unbeaten run per season (within season) ===\n";
    for (const Season &s : seasons)
    {
        UnbeatenStreak u = longestUnbeatenInSeason(s);
        out << s.label << ": " << u.team << "  " << u.length << " games  (" << u.from_date << " → " << u.to_date << ")\n";
    }
    out << "\n";

    out << "=== Year-over-year point changes (consecutive seasons, same club) ===\n";
    auto yoy = yearOverYearDeltas(seasons);
    sort(yoy.begin(), yoy.end(), [](const YoYRow &a, const YoYRow &b) {
        if (a.points_delta != b.points_delta)
            return a.points_delta > b.points_delta;
        return a.team < b.team;
    });
    size_t cap = min<size_t>(40, yoy.size());
    for (size_t i = 0; i < cap; ++i)
    {
        const YoYRow &r = yoy[i];
        out << r.team << "  " << r.from_season << "→" << r.to_season << "  pts " << r.from_points << "→" << r.to_points
            << " (Δ" << r.points_delta << ")  rank " << r.from_rank << "→" << r.to_rank << " (Δ " << r.rank_delta << ")\n";
    }
    out << "\n";

    out << "=== Best defense (fewest goals conceded) per season — top 5 ===\n";
    for (const Season &s : seasons)
    {
        out << "Season " << s.label << "\n";
        auto def = bestDefense(s, 5);
        int i = 1;
        for (const DefenseRow &d : def)
            out << "  " << i++ << ". " << left << setw(28) << d.team << " GA " << d.ga << "  GA/GP " << fixed
                << setprecision(3) << d.ga_per_game << "\n";
        out << "\n";
    }
}
