#include "nitro/types.h"

int DecodeStateAt4604(int object);
int NNS_G2dGetImageLocation(int *array, int index);

/* Round byte size up to mapping boundary blocks */
u32 DispObj_GetCharBlockCount(int manager, u8 *image)
{
    u32 blocks;
    u32 size = NNS_G2dGetImageLocation((int *)(image + 0x38), DecodeStateAt4604(manager));
    switch ((*(int *)(image + 0xc) >> 20) & 3) {
    case 0:
        blocks = (size + 0x1f) >> 5;
        break;
    case 1:
        blocks = (size + 0x3f) >> 6;
        break;
    case 2:
        blocks = (size + 0x7f) >> 7;
        break;
    case 3:
        blocks = (size + 0xff) >> 8;
        break;
    }
    return blocks;
}
