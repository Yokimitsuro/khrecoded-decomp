#include "nitro/types.h"

typedef struct {
    u16 pad00;
    u16 kind;
    int mode;
    u8 pad08[4];
    int score;
} ScoreEntry;

int GetRemainingScoreTens(ScoreEntry *entry)
{
    int limit = 0;
    int score = entry->score;

    if (entry->mode == 1) {
        limit = 600000;
    } else if (entry->mode == 2) {
        limit = 300000;
    } else {
        switch (entry->kind) {
        case 0:
            limit = 600000;
            break;
        case 6:
            limit = 600000;
            break;
        case 7:
            limit = 600000;
            break;
        case 8:
            limit = 300000;
            break;
        }
    }
    score -= score % 10;
    if (limit >= score) {
        return (limit - score) / 10;
    }
    return 0;
}

