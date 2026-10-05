#include "nitro/types.h"

extern void PlaceCursorNode(void);
extern void ShowUnlockedPageTabs(void *entity);
extern void RefreshPageTabs(void *entity);
extern void func_ov078_020c49a0(void *entity);
extern void DrawPageHeader(void *entity);

/* Runs a fixed init sequence on an entity */
void InitSequence(void *entity)
{
    PlaceCursorNode();
    func_ov078_020c49a0(entity);
    *(u32 *)((u8 *)entity + 0x5d4) = 0;
    ShowUnlockedPageTabs(entity);
    RefreshPageTabs(entity);
    DrawPageHeader(entity);
}
