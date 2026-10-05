#include "nitro/types.h"

typedef void (*GaugeCellFn)(void *target, int cell, int mode);

typedef struct GaugeCounts {
    u16 total;
    u16 previous;
    u16 cellSize;
} GaugeCounts;

BOOL RedrawGaugeCells(void *target, u16 value, u16 scale, GaugeCounts *counts, GaugeCellFn draw, BOOL rebuild)
{
    int mode;
    int divisor;
    int previous;
    int maxCells;
    int oldCells;
    int newCells;
    int i;

    previous = counts->previous;
    divisor = counts->total;
    oldCells = (u16)(previous * scale / divisor);
    newCells = (u16)(value * scale / divisor);

    maxCells = (u16)(divisor * scale / counts->cellSize);

    if (previous == 0) {
        if (value != 0 && newCells == 0) {
            newCells = 1;
        }
    } else if (newCells == 0) {
        if (oldCells == 0) {
            oldCells = 1;
        }
        if (value != 0) {
            newCells = 1;
        }
    }
    counts->previous = value;

    if (rebuild) {
        if (target != NULL) {
            for (i = 0; i < newCells; i++) {
                draw(target, i, 0);
            }
            for (; i < maxCells; i++) {
                draw(target, i, 1);
            }
        }
    } else {
        if (oldCells == newCells) {
            return FALSE;
        }
        if ((u32)newCells > (u32)oldCells) {
            mode = 0;
        } else {
            int swap = oldCells;

            mode = 1;
            oldCells = newCells;
            newCells = swap;
        }
        if (target != NULL) {
            for (; oldCells < newCells; oldCells++) {
                if (mode == 1 && oldCells > scale) {
                    draw(target, oldCells, 4);
                } else {
                    draw(target, oldCells, mode);
                }
            }
        }
    }
    return TRUE;
}
