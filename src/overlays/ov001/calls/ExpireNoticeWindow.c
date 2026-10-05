#include "nitro/types.h"

typedef struct NoticeScreen {
    u8 pad_000[0x1C];
    u8 records[0x3F0];
    u64 shownTick;
    u8 pad_414[0x44];
    void *tilemap;
} NoticeScreen;

extern u64 OS_GetTick(void);
extern void *FindActiveRecordById(void *records, int id);
extern void func_ov027_020b8288(void *records, void *record);
extern void func_ov027_020b9d74(NoticeScreen *screen, int layer, int x, int y, int width, int height);
extern void ClearTilemapRegion(void *dest, int column, int row, int width, int height);

void ExpireNoticeWindow(NoticeScreen *screen)
{
    u64 now = OS_GetTick();

    if (screen->shownTick != 0 && now >= screen->shownTick + 0x17F898) {
        if (screen->tilemap == NULL) {
            func_ov027_020b8288(screen->records, FindActiveRecordById(screen->records, 0x34));
            func_ov027_020b9d74(screen, 11, 1, 7, 8, 1);
        } else {
            ClearTilemapRegion(screen->tilemap, 0, 5, 13, 4);
        }
        screen->shownTick = 0;
    }
}
