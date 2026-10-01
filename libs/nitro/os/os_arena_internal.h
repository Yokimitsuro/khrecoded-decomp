#ifndef NITRO_OS_ARENA_INTERNAL_H
#define NITRO_OS_ARENA_INTERNAL_H

typedef int BOOL;

typedef enum OSArenaId {
    OS_ARENA_MAIN = 0,
    OS_ARENA_MAIN_SUBPRIV = 1,
    OS_ARENA_MAINEX = 2,
    OS_ARENA_ITCM = 3,
    OS_ARENA_DTCM = 4,
    OS_ARENA_SHARED = 5,
    OS_ARENA_WRAM_MAIN = 6
} OSArenaId;

typedef struct OSArenaState {
    BOOL initialized;
    BOOL mainExArenaEnabled;
} OSArenaState;

extern OSArenaState OSi_ArenaState;

void *OS_GetInitArenaHi(OSArenaId arena);
void *OS_GetInitArenaLo(OSArenaId arena);
void OS_SetArenaHi(OSArenaId arena, void *address);
void OS_SetArenaLo(OSArenaId arena, void *address);

#endif