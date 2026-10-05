#include "nitro/types.h"

typedef struct Ov024Board {
    u8 pad_00[0x27];
    s8 firstPick;
    s8 secondPick;
    u8 slotKinds[6];
    u8 pad_2F[2];
    s8 slotValues[6];
    u8 slotRandoms[6];
    u8 pad_3D[0x55 - 0x3D];
    s8 startPick;
    u8 slotBonuses[6];
    u8 flags5C;
    u8 flags5D;
    u8 pad_5E;
    u8 counter5F;
    u8 counter60;
    u8 pad_61;
    s8 bonusCount;
    u8 defaultKind;
    u8 pad_64[5];
    s8 fillMin;
    s8 fillMax;
    u8 pad_6B;
    s8 bonusMin;
    s8 bonusMax;
    u8 pad_6E[0x7C - 0x6E];
    int needsReset;
} Ov024Board;

typedef struct Ov024State {
    u8 pad_00[8];
    Ov024Board *board;
} Ov024State;

extern Ov024State data_ov024_020b7540;
extern u32 func_0202a9e4(u16 range);
extern void FillRandomEmptySlots(Ov024Board *board, int count);
extern void PlaceBoardBonuses(Ov024Board *board);
extern void GenerateRandomLinks(Ov024Board *board);

void RerollBoardSlots(Ov024Board *board) {
    int i;
    int fillCount;
    int pick;
    int seen;

    if (board->needsReset == 0) {
        return;
    }
    board->needsReset = 0;
    for (i = 0; i < 6; i++) {
        board->slotValues[i] = -1;
        board->slotRandoms[i] = func_0202a9e4(4);
        board->slotBonuses[i] = 0;
        board->slotKinds[i] = board->defaultKind;
    }
    board->flags5C = 0;
    board->flags5D = 0;
    board->counter5F = 0;
    board->counter60 = 0;
    fillCount = board->fillMin + func_0202a9e4((u16)(board->fillMax - board->fillMin + 1));
    board->bonusCount = board->bonusMin + func_0202a9e4((u16)(board->bonusMax - board->bonusMin + 1));
    FillRandomEmptySlots(data_ov024_020b7540.board, fillCount);

    if (board->slotValues[2] < 0 && board->slotValues[3] < 0) {
        board->slotValues[2] = board->slotValues[4];
        board->slotValues[3] = board->slotValues[5];
        board->slotValues[5] = -1;
        board->slotValues[4] = board->slotValues[5];
    }
    if (board->slotValues[0] < 0 && board->slotValues[1] < 0) {
        board->slotValues[0] = board->slotValues[2];
        board->slotValues[1] = board->slotValues[3];
        board->slotValues[2] = board->slotValues[4];
        board->slotValues[3] = board->slotValues[5];
        board->slotValues[5] = -1;
        board->slotValues[4] = board->slotValues[5];
    }
    if (board->slotValues[0] < 0 && board->slotValues[2] < 0 && board->slotValues[4] < 0) {
        board->slotValues[0] = board->slotValues[1];
        board->slotValues[2] = board->slotValues[3];
        board->slotValues[4] = board->slotValues[5];
        board->slotValues[5] = -1;
        board->slotValues[3] = board->slotValues[5];
        board->slotValues[1] = board->slotValues[3];
    }
    PlaceBoardBonuses(data_ov024_020b7540.board);
    GenerateRandomLinks(board);

    pick = func_0202a9e4(fillCount);
    seen = 0;
    for (i = 0; i < 6; i++) {
        if (board->slotValues[i] >= 0 && pick == seen++) {
            board->firstPick = i;
        }
    }
    pick = func_0202a9e4(fillCount);
    seen = 0;
    for (i = 0; i < 6; i++) {
        if (board->slotValues[i] >= 0 && pick == seen++) {
            board->secondPick = i;
        }
    }
    board->startPick = board->firstPick;
}
