#pragma once

#include "common.h"

#define FPS_LIMIT 60

#define DEFAULT_WIDTH 640
#define DEFAULT_HEIGHT 480

#define TITLE "TimeCo: Time Commando"

typedef enum {
    TIMECO_UNKNOWN,
    TIMECO_EU,
    TIMECO_US,
    TIMECO_JP,
    TIMECO_ASIA,
    TIMECO_DEMO,
    TIMECO_MCAFEE_DEMO,
} game_type_e;


game_type_e detect_game();

const c8* get_game_title();
