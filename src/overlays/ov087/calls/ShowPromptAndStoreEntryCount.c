#include "nitro/types.h"

extern int GetPlayerEntryCount(int player, u32 id);
extern void *func_ov027_020ba2c8(void *container, int index);
extern void func_ov087_020c4880(void *scene, const u16 *text);
extern void WriteSessionPackedBits(int bitOffset, u32 bitCount, u32 value);

void ShowPromptAndStoreEntryCount(u8 *scene)
{
    int count = GetPlayerEntryCount(0, 9);

    func_ov087_020c4880(scene, func_ov027_020ba2c8(scene + 0xb64, 0x18));
    WriteSessionPackedBits(0x1a0f, 3, count);
}

