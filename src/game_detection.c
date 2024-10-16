#include "lib/file_system.h"

#include "game_detection.h"

inline game_type_e detect_game() {
    if (file_exists("RESSOURC.HQR")) {
        return TIMECO_EU;
    }
    // TODO Add more game detection
    return TIMECO_UNKNOWN;
}

inline const c8* get_game_title() {
    return TITLE;
}
