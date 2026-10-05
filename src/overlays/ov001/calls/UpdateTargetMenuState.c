#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MenuRequest {
    u32 kind;
    u8 pad_04[0x4];
} MenuRequest;

typedef struct MenuContext {
    u32 flags;
    MenuRequest request;
    u8 pad_0c[0x20];
    fx32 fadeLevels[3];
} MenuContext;

typedef struct EntryCallbacks EntryCallbacks;

struct EntryCallbacks {
    u8 pad_000[0x21c];
    u32 (*getFlags)(EntryCallbacks *entry);
};

extern MenuContext *NNSi_FndGetCurrentRootHeap(void);
extern void UpdateStageEventMessage(int id);
extern BOOL func_ov001_0206bc0c(void);
extern u32 func_ov001_02064490(void);
extern void ResetPendingRequest(void);
extern EntryCallbacks *GetBoundedEntryField(int index);
extern BOOL FindNearestTargetInRange(MenuRequest *result, void *origin);
extern void SetMenuOpenState(int open, BOOL withSound);
extern void CloseMenuIfTargetLost(void);
extern void UpdateTargetMenu(void);
extern void ApplyPendingTargetRequest(void);

static inline fx32 StepFadeLevel(fx32 level)
{
    level += 0x1000;
    if (level > 0xf000) {
        level = 0xf000;
    } else if (level < 0) {
        level = 0;
    }
    return level;
}

int UpdateTargetMenuState(void)
{
    MenuContext *menu = NNSi_FndGetCurrentRootHeap();
    BOOL keepTarget;

    UpdateStageEventMessage(-1);
    if (menu->flags & 4) {
        return 0;
    }
    if (func_ov001_0206bc0c() || func_ov001_02064490()) {
        ResetPendingRequest();
        return 0;
    }
    keepTarget = TRUE;
    if (!(menu->flags & 2)) {
        keepTarget = FALSE;
        if (menu->request.kind == 1 || menu->request.kind == 3) {
            u32 entryFlags = 0;
            EntryCallbacks *entry = GetBoundedEntryField(0);

            if (entry->getFlags != NULL) {
                entryFlags = entry->getFlags(entry);
            }
            if (entryFlags & 4) {
                keepTarget = TRUE;
            }
        }
        if (!keepTarget) {
            if (FindNearestTargetInRange(&menu->request, NULL)) {
                SetMenuOpenState(TRUE, FALSE);
            } else {
                SetMenuOpenState(FALSE, FALSE);
            }
        }
    }
    if (keepTarget) {
        CloseMenuIfTargetLost();
    }
    if (menu->flags & 8) {
        UpdateTargetMenu();
    }
    menu->fadeLevels[0] = StepFadeLevel(menu->fadeLevels[0]);
    menu->fadeLevels[1] = StepFadeLevel(menu->fadeLevels[1]);
    menu->fadeLevels[2] = StepFadeLevel(menu->fadeLevels[2]);
    ApplyPendingTargetRequest();
    return 0;
}
