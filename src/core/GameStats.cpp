/**********************************************************************************
 * Project: MINI JAME GAM #39
 * Authors: Alexis BOITEL, Justine LOIZEL & Augustin BOST
 * Date, Location: 2025, Rennes
 **********************************************************************************/

 #include "GameStats.hpp"

int GameStats::finalBonus = 0;
float GameStats::finalTime = 0.0f;

void GameStats::reset() {
    finalBonus = 0;
    finalTime = 0.0f;
}