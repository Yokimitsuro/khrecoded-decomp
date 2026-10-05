#include "nitro/types.h"

typedef struct {
    u8 pad[0x128];
    void *cells;
    int *firstSlots;
    int *secondSlots;
} ScoreScreen;

extern void SetDigitDisplay(void *cells, int first, int value, void *origin);
extern void SetEntrySlotsVisible(void *cells, int *slots, u16 visible);

void SetScoreDisplay(ScoreScreen *screen, int digitsA, int digitsB, int digitsC,
                              int valueC, u16 firstVisible, u16 secondVisible)
{
    SetDigitDisplay(screen->cells, digitsA, -1, NULL);
    SetDigitDisplay(screen->cells, digitsB, -1, NULL);
    SetDigitDisplay(screen->cells, digitsC, valueC, NULL);
    SetEntrySlotsVisible(screen->cells, screen->firstSlots, firstVisible);
    SetEntrySlotsVisible(screen->cells, screen->secondSlots, secondVisible);
}
