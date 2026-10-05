#include "nitro/types.h"

typedef struct Ov024Board {
    u8 pad_00[0x31];
    s8 slotValues[6];
    u8 pad_37[0x3d - 0x37];
    s8 links[6][4];
} Ov024Board;

extern u32 func_0202a9e4(u32 range);
extern int GetLinkDistance(s8 *nodeValues, s8 (*links)[4], int startNode, int goalNode);
extern BOOL func_ov024_020b63e4(s8 *nodeValues, s8 (*links)[4], int first, int second);

void GenerateRandomLinks(Ov024Board *board)
{
    int second;
    int firstSeed = func_0202a9e4(100);
    int secondSeed = func_0202a9e4(100);
    int node;
    int dir;
    int first;
    int remaining;
    int step;

    for (node = 0; node < 6; node++) {
        for (dir = 0; dir < 4; dir++) {
            board->links[node][dir] = -1;
        }
    }
    for (node = 0; node < 5; node++) {
        first = (node + firstSeed) % 5;
        remaining = 5 - first;
        for (step = 0; step < remaining; step++) {
            second = first + (step + secondSeed) % remaining;
            if (GetLinkDistance(board->slotValues, board->links, first, second + 1) < 0 || func_0202a9e4(100) < 20) {
                func_ov024_020b63e4(board->slotValues, board->links, first, second + 1);
            }
        }
    }
}
