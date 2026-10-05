#include "nitro/types.h"

typedef struct VramBlock {
    u32 pad00;
    u32 size;
    u8 pad08[0x30];
    int offsets[10];
    struct VramBlock *next;
} VramBlock;

typedef struct VramManager {
    u8 pad[0x460c];
    u32 firstFree;
    u8 pad4610[8];
    VramBlock *head;
} VramManager;

typedef struct VramRequest {
    u8 pad[0x10];
    u32 size;
} VramRequest;

int DecodeStateAt4604(VramManager *manager);
int NNS_G2dGetImageLocation(int *array, int index);

u32 FindFreeVramGapOffset(VramManager *manager, VramRequest *request)
{
    VramBlock *block = manager->head;
    int mode;
    u32 result = manager->firstFree;
    mode = DecodeStateAt4604(manager);

    /* First gap large enough, else after the last block */
    while (block != NULL) {
        u32 offset = NNS_G2dGetImageLocation(block->offsets, mode);
        u32 end;
        u32 nextOffset;
        if (block->next == NULL) {
            result = offset + block->size;
            break;
        }
        nextOffset = NNS_G2dGetImageLocation(block->next->offsets, mode);
        end = offset + block->size;
        if (request->size <= nextOffset - end) {
            result = end;
            break;
        }
        block = block->next;
    }
    return result;
}


