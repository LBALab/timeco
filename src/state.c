#include "state.h"
#include "common.h"
#include "game_detection.h"


inline void state_init(state_t *state) {
    state->system.quit = false;
    state->system.title = TITLE;
    state->game_type = TIMECO_UNKNOWN;
}

inline void state_release(state_t *state) {
    memory_free(state);
}
