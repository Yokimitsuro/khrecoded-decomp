#include "nitro/types.h"

void UnlinkNodeFromList(s32 *node) {
    s32 *list = (s32 *)node[0];

    if (list != NULL) {
        if (node[1] != 0) {
            *(s32 *)(node[1] + 8) = node[2];
        }
        if (node[2] != 0) {
            *(s32 *)(node[2] + 4) = node[1];
        }
        if ((s32 *)node == *(s32 **)((u8 *)list + 8)) {
            *(s32 *)((u8 *)list + 8) = node[1];
        }
        node[2] = 0;
        node[1] = 0;
        node[0] = 0;
    }
}
