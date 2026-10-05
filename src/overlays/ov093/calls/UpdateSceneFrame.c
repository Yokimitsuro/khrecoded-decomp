#include "nitro/types.h"

typedef struct SceneWork SceneWork;

typedef void (*SceneStateHandler)(SceneWork *work);

struct SceneWork {
    u8 pad_0000[0xd1d8];
    int blinkTimer;
    int blinkPhase;
};

extern const SceneStateHandler gTrophyReportStateHandlers[];
extern int func_ov093_020c2368(SceneWork *work);
extern void RedrawEntryPanelText(int index, SceneWork *work);
extern void UpdateScrollBarDrag(SceneWork *work);
extern void func_ov093_020c0310(SceneWork *work);

void UpdateSceneFrame(SceneWork *work)
{
    SceneStateHandler handler = gTrophyReportStateHandlers[func_ov093_020c2368(work)];

    if (handler != NULL) {
        handler(work);
    }
    if (++work->blinkTimer >= 60) {
        work->blinkTimer = 0;
        work->blinkPhase = (work->blinkPhase + 1) % 2;
        RedrawEntryPanelText(0, work);
    }
    if (func_ov093_020c2368(work) == 6) {
        UpdateScrollBarDrag(work);
    }
    func_ov093_020c0310(work);
}
