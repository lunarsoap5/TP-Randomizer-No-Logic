#pragma once

#include "defines.h"

namespace mod::stage
{
    extern char allStages[76][8];
    extern const char* dungeonStages[18];
    extern const char* bossStages[8];
    extern const char* shopStages[8];
    extern const char* grottoStages[5];
    extern const char* caveStages[6];
    extern const char* interiorStages[8];
    extern const char* specialStages[3];
    extern const char* timeOfDayStages[18];
    extern const char* mainDungeonStages[9];
    extern const char* allDungeonStages[26];
    extern const char* keyRegions[11];

    enum stageIDs : u8
    { 
        Lakebed_Temple,
        Goron_Mines,
        Forest_Temple,
        Temple_of_Time,
        City_in_the_Sky,
        Palace_of_Twilight,
        Hyrule_Castle,
        Arbiters_Grounds,
        Snowpeak_Ruins,
        Faron_Woods,
        Bulblin_Camp
    };
}     // namespace mod::stage