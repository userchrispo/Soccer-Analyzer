#include <vector>
#include <unordered_map>
#include "model.hpp"
#include "stats.hpp"

unordered_map<string, TeamStats> computeTeamStats(const vector<Match> &matches)
{

    unordered_map<string, TeamStats> teams;

    for (const auto &m : matches)
    {
        teams[m.home_team].recordResult(m.home_goals, m.away_goals, m.home_clearances, m.home_corners, m.home_fouls_conceded, m.home_offsides, m.home_passes, m.home_shots, m.home_shots_on_target, m.home_tackles, m.home_touches, m.home_red_cards, m.home_yellow_cards, m.home_possession, m.away_shots_on_target, m.away_shots, m.away_corners);

        teams[m.away_team].recordResult(m.away_goals, m.home_goals, m.away_clearances, m.away_corners, m.away_fouls_conceded, m.away_offsides, m.away_passes, m.away_shots, m.away_shots_on_target, m.away_tackles, m.away_touches, m.away_red_cards, m.away_yellow_cards, m.away_possession, m.home_shots_on_target, m.home_shots, m.home_corners);
    }

    return teams;
}

void advancedStats(unordered_map<string, TeamStats> &teams)
{

    // in order to calculate the normalize value we first need to get the max/min of all values
    // xOFF
    int min_shots = INT_MAX;
    int max_shots = -1;

    int min_sot = INT_MAX;
    int max_sot = -1;

    int min_corners = INT_MAX;
    int max_corners = -1;

    int min_passes = INT_MAX;
    int max_passes = -1;

    double min_possession = 1e9;
    double max_possession = -1e9;

    int min_touches = INT_MAX;
    int max_touches = -1;

    // tOFF

    int min_gf = INT_MAX;
    int max_gf = -1;

    double max_shot_conversion = -1e9;
    double min_shot_conversion = 1e9;

    double min_sot_conversion = 1e9;
    double max_sot_conversion = -1e9;

    // xDEF

    int min_corners_against = INT_MAX;
    int max_corners_against = -1;

    int min_shots_against = INT_MAX;
    int max_shots_against = -1;

    int min_sot_against = INT_MAX;
    int max_sot_against = -1;

    double min_cleareance_eff = 1e9;
    double max_clearance_eff = -1e9;

    // tDEF

    int min_ga = INT_MAX;
    int max_ga = -1;
    double min_shot_against_conversion = 1e9;
    double max_shot_against_conversion = -1e9;

    double min_sot_against_conversion = 1e9;
    double max_sot_against_conversion = -1e9;

    // Discpline

    int min_yellow_cards = INT_MAX;
    int max_yellow_cards = -1;

    int min_red_cards = INT_MAX;
    int max_red_cards = -1;

    int min_fouls_conceded = INT_MAX;
    int max_fouls_conceded = -1;

    int min_offsides = INT_MAX;
    int max_offsides = -1;

    // control

    for (auto &team : teams)
    {
        TeamStats &curr = team.second;

        // xOFF
        min_shots = min(min_shots, curr.shots);
        max_shots = max(max_shots, curr.shots);

        min_sot = min(min_sot, curr.shots_on_target);
        max_sot = max(max_sot, curr.shots_on_target);

        min_corners = min(min_corners, curr.corners);
        max_corners = max(max_corners, curr.corners);

        min_passes = min(min_passes, curr.passes);
        max_passes = max(max_passes, curr.passes);

        min_possession = min(min_possession, curr.avgPossession());
        max_possession = max(max_possession, curr.avgPossession());

        min_touches = min(min_touches, curr.touches);
        max_touches = max(max_touches, curr.touches);

        // tOFF

        curr.shot_conversion = (curr.shots > 0) ? (double)curr.gf / curr.shots : 0;
        curr.sot_conversion = (curr.shots_on_target > 0) ? (double)curr.gf / curr.shots_on_target : 0;

        min_gf = min(min_gf, curr.gf);
        max_gf = max(max_gf, curr.gf);

        min_shot_conversion = min(min_shot_conversion, curr.shot_conversion);
        max_shot_conversion = max(max_shot_conversion, curr.shot_conversion);

        min_sot_conversion = min(min_sot_conversion, curr.sot_conversion);
        max_sot_conversion = max(max_sot_conversion, curr.sot_conversion);

        // xDEF
        min_corners_against = min(min_corners_against, curr.corners_against);
        max_corners_against = max(max_corners_against, curr.corners_against);

        min_shots_against = min(min_shots_against, curr.shots_against);
        max_shots_against = max(max_shots_against, curr.shots_against);

        min_sot_against = min(min_sot_against, curr.sot_against);
        max_sot_against = max(max_sot_against, curr.sot_against);

        curr.clearance_eff = (curr.shots_against > 0) ? (double)curr.clearances / curr.shots_against : 0;

        min_cleareance_eff = min(min_cleareance_eff, curr.clearance_eff);
        max_clearance_eff = max(max_clearance_eff, curr.clearance_eff);

        // tDEF

        min_ga = min(min_ga, curr.ga);
        max_ga = max(max_ga, curr.ga);

        curr.shot_against_conversion = (curr.shots_against > 0) ? (double)curr.ga / curr.shots_against : 0;
        curr.sot_against_conversion = (curr.sot_against > 0) ? (double)curr.ga / curr.sot_against : 0;

        min_shot_against_conversion = min(min_shot_against_conversion, curr.shot_against_conversion);
        max_shot_against_conversion = max(max_shot_against_conversion, curr.shot_against_conversion);

        min_sot_against_conversion = min(min_sot_against_conversion, curr.sot_against_conversion);
        max_sot_against_conversion = max(max_sot_against_conversion, curr.sot_against_conversion);

        // Discpline

        min_yellow_cards = min(min_yellow_cards, curr.yellow_cards);
        max_yellow_cards = max(max_yellow_cards, curr.yellow_cards);

        min_red_cards = min(min_red_cards, curr.red_cards);
        max_red_cards = max(max_red_cards, curr.red_cards);

        min_fouls_conceded = min(min_fouls_conceded, curr.fouls_conceded);
        max_fouls_conceded = max(max_fouls_conceded, curr.fouls_conceded);

        min_offsides = min(min_offsides, curr.offsides);
        max_offsides = max(max_offsides, curr.offsides);
    }

    // after we get the min/max of all the stats we can normalize each individual teams stat

    for (auto &team : teams)
    {
        {

            TeamStats &curr = team.second;

            // xOFF

            curr.shots_norm = (curr.shots - min_shots) / (max_shots - min_shots);
            curr.sot_norm = (curr.shots_on_target - min_sot) / (max_sot - min_sot);
            curr.corners_norm = (curr.corners - min_corners) / (max_corners - min_corners);
            curr.passes_norm = (curr.passes - min_passes) / (max_passes - min_passes);
            curr.possession_norm = (curr.avgPossession() - min_possession) / (max_possession - min_possession);
            curr.touches_norm = (curr.touches - min_touches) / (max_touches - min_touches);

            // tOF
            curr.gf_norm = (curr.gf - min_gf) / (max_gf - min_gf);
            curr.shot_conversion_norm = (curr.shot_conversion - min_shot_conversion) / (max_shot_conversion - min_shot_conversion);
            curr.sot_conversion_norm = (curr.sot_conversion - min_sot_conversion) / (max_sot_conversion - min_sot_conversion);

            // xDEF

            curr.corners_against_norm = (curr.corners_against - min_corners_against) / (max_corners_against - min_corners_against);
            curr.clearance_eff_norm = (curr.clearance_eff - min_cleareance_eff) / (max_clearance_eff - min_cleareance_eff);
            curr.shots_against_norm = (curr.shots_against - min_shots_against) / (max_shots_against - min_shots_against);
            curr.sot_against_norm = (curr.sot_against - min_sot_against) / (max_sot_against - min_sot_against);

            // tDEF
            curr.ga_norm = (curr.ga - min_ga) / (max_ga - min_ga);
            curr.shot_against_conversion_norm = (curr.shot_against_conversion - min_shot_against_conversion) / (max_shot_against_conversion - min_shot_against_conversion);
            curr.sot_against_conversion_norm = (curr.sot_against_conversion - min_sot_against_conversion) / (max_sot_against_conversion - min_sot_against_conversion);

            // Discpline
            curr.yellow_cards_norm = (curr.yellow_cards - min_yellow_cards) / (max_yellow_cards - min_yellow_cards);
            curr.red_cards_norm = (curr.red_cards - min_red_cards) / (max_red_cards - min_red_cards);
            curr.fouls_conceded_norm = (curr.fouls_conceded - min_fouls_conceded) / (max_fouls_conceded - min_fouls_conceded);
            curr.offsides_norm = (curr.offsides - min_offsides) / (max_offsides - min_offsides);

            // after stats are normalized we can now calculate each teams xOFF, tOFF, xDEF, tDEF, Discipline, control score.

            curr.xOFF = (curr.shots_norm * 0.20) + (curr.sot_norm * 0.30) + (curr.corners_norm * 0.15) + (curr.possession_norm * 0.15) + (curr.passes_norm * 0.10) + (curr.touches_norm * 0.10);

            curr.tOFF = (curr.gf_norm * 0.50) + (curr.shot_conversion_norm * 0.25) + (curr.sot_conversion_norm * 0.25);

            curr.xDEF = (curr.corners_against_norm * -0.15) + (curr.shots_against_norm * -0.25) + (curr.sot_against_norm * -0.35) + (curr.clearance_eff_norm * 0.25);

            curr.tDEF = (curr.ga_norm * -0.50) + (curr.shot_against_conversion_norm * -0.25) + (curr.sot_against_conversion_norm * -0.25);

            curr.discipline_score = (curr.yellow_cards_norm * -0.20) + (curr.red_cards_norm * -0.45) + (curr.fouls_conceded_norm * -0.25) + (curr.offsides_norm * -0.10);

            curr.control_score = (curr.possession_norm * 0.50) + (curr.passes_norm * 0.30) + (curr.touches_norm * 0.20);

            curr.final_score = (curr.xOFF * 0.25) + (curr.tOFF * 0.25) + (curr.xDEF * 0.20) + (curr.tDEF * 0.20) + (curr.discipline_score * -0.05) + (curr.control_score * 0.15);
        }
    }
}
