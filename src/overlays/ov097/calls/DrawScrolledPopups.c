#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x14];
    fx32 y;
    u8 pad_18[0x14];
} PopupEntry;

typedef struct {
    int entryIndex;
    u8 pad_0004[0xeea8 - 4];
    PopupEntry popups[10];
    int popupCount;
    u8 pad_f064[4];
    int scrollRow;
} MenuScene;

extern void func_ov097_020c19cc(void);
extern BOOL IsEntryFlagSet_020c1494(int flagSet, int entryIndex);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void func_ov097_020c1db8(void *list);
extern void func_ov097_020c1a64(void);

#define ROW_TO_FX32(row) ((fx32)((float)(row) > 0 ? 0.5f + 4096.0f * (float)(row) : 4096.0f * (float)(row) - 0.5f))

void DrawScrolledPopups(MenuScene *scene)
{
    int entryIndex = scene->entryIndex;
    PopupEntry popup;
    int i;

    func_ov097_020c19cc();
    if (IsEntryFlagSet_020c1494(0, entryIndex)) {
        for (i = 0; i < scene->popupCount; i++) {
            MI_CpuCopy8(&scene->popups[i], &popup, sizeof(PopupEntry));
            popup.y += ROW_TO_FX32(scene->scrollRow);
            func_ov097_020c1db8(&popup);
        }
    }
    func_ov097_020c1a64();
}
