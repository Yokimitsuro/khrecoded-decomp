#include "nitro/types.h"

typedef struct {
    int type;
    union {
        int value;
        struct {
            u16 low;
            u16 high;
        } half;
    } arg;
} ScoreEvent;

typedef struct {
    u8 pad0;
    u8 dirty;
    u8 pad2;
    u8 eventCount;
    u16 digitsA;
    u16 pad6;
    u16 digitsB;
    u16 digitsC;
    u8 padC[4];
    ScoreEvent events[16];
    u8 pad90[3];
    s8 markIndex;
    s16 markValue;
    s16 fieldA;
    u8 pad98[0xc];
    s16 fieldB;
    s16 fieldC;
    s16 fieldD;
    s16 fieldE;
    s16 fieldF;
    u8 padAE[0x7a];
    void *cells;
    int *firstSlots;
    int *secondSlots;
} ScoreScreen;

extern u8 *data_0205fe0c;

extern void SetDigitDisplay(void *cells, int first, int value, void *origin);
extern void SetEntrySlotsVisible(void *cells, int *slots, u16 visible);
extern void SetScoreDisplay(ScoreScreen *screen, int digitsA, int digitsB, int digitsC,
                                     int valueC, u16 firstVisible, u16 secondVisible);

void ApplyScoreEvents(ScoreScreen *screen)
{
    u8 *state = data_0205fe0c;
    s16 i;

    for (i = 0; i < screen->eventCount; i++) {
        ScoreEvent *event = &screen->events[i];
        void *cells = screen->cells;
        u32 best;
        u32 value;

        switch (event->type) {
        case 0:
            screen->markValue = -1;
            screen->fieldA = -1;
            screen->fieldB = -1;
            screen->fieldC = -1;
            screen->fieldD = -1;
            screen->fieldE = -1;
            screen->fieldF = -1;
            screen->markIndex = -1;
            SetDigitDisplay(cells, screen->digitsA, *(int *)(state + 0x28d0), NULL);
            SetDigitDisplay(cells, screen->digitsB, -1, NULL);
            SetDigitDisplay(cells, screen->digitsC, -1, NULL);
            SetEntrySlotsVisible(cells, screen->secondSlots, 0);
            SetEntrySlotsVisible(cells, screen->firstSlots, 0);
            break;
        case 1:
            value = event->arg.value;
            best = *(u32 *)(state + 0x28d0);
            if (best > value) {
                SetScoreDisplay(screen, screen->digitsA, screen->digitsB, screen->digitsC, value, 0, 1);
            } else if (best < value) {
                SetScoreDisplay(screen, screen->digitsA, screen->digitsC, screen->digitsB, value, 1, 0);
            } else {
                SetScoreDisplay(screen, screen->digitsB, screen->digitsC, screen->digitsA, best, 0, 0);
            }
            break;
        case 2:
            if (event->arg.value < 0) {
                screen->markValue = -1;
                screen->fieldA = -1;
                screen->markIndex = -1;
            } else {
                screen->markValue = event->arg.half.high;
                screen->markIndex = event->arg.half.low;
                screen->fieldA = -1;
            }
            break;
        case 3:
            screen->fieldA = (s8)event->arg.value;
            break;
        case 4:
            screen->fieldB = event->arg.value;
            break;
        case 5:
            screen->fieldC = event->arg.value;
            break;
        case 6:
            screen->fieldD = event->arg.value;
            break;
        case 7:
            screen->fieldE = event->arg.value;
            break;
        case 8:
            screen->fieldF = event->arg.value;
            break;
        }
        screen->dirty = 1;
    }
    screen->eventCount = 0;
}
