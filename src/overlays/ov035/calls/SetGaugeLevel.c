#include "nitro/types.h"

typedef struct GaugeWork {
    u8 unknown_000[0x18];
    int level;
    u8 unknown_01c[0x114];
    int fill;
} GaugeWork;

typedef struct GaugeGlobals {
    void *unknown_00;
    GaugeWork *work;
} GaugeGlobals;

extern GaugeGlobals data_ov035_020bc508;
extern void *GetSceneTagTracker(void);
extern void *FindLoadedElementById(void *pool, int id);
extern void SetTagRecordArmed(void *pool, void *record, int armed);
extern void *FindActiveRecordById(void *pool, int id);
extern void func_ov027_020b8230(void *pool, void *record);
extern void QueueColorUpload(BOOL high);

void SetGaugeLevel(int level) {
    GaugeWork *work = data_ov035_020bc508.work;
    void *pool = GetSceneTagTracker();

    if (work == NULL) {
        return;
    }
    if (level == 100) {
        SetTagRecordArmed(pool, FindLoadedElementById(pool, 1), 1);
    } else if (work->level == 100) {
        SetTagRecordArmed(pool, FindLoadedElementById(pool, 1), 0);
        func_ov027_020b8230(pool, FindActiveRecordById(pool, 5));
    }
    if (level > 0) {
        work->fill = (level * 87) / 100;
    } else {
        work->fill = 0;
    }
    QueueColorUpload(level >= 40);
    work->level = level;
}
