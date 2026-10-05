#include "nitro/types.h"

typedef struct Ov038HandlerTable {
    void *start;
    void *isIdle;
    void *update;
    void *setMode;
    void *hasObject;
    void *release;
    void *reserved0;
    void *pause;
    void *reserved1[2];
    void *resume;
} Ov038HandlerTable;

extern void func_ov038_020ba61c(void);
extern void IsOv038SoundCtxFlag0Clear(void);
extern void func_ov038_020ba66c(void);
extern void SetSoundCtxMode(void);
extern void HasOv038ObjectField28(void);
extern void ReleaseOv038Object(void);
extern void func_ov038_020ba6f8(void);
extern void func_ov038_020ba700(void);

void InitOv038HandlerTable(Ov038HandlerTable *table)
{
    table->start = func_ov038_020ba61c;
    table->isIdle = IsOv038SoundCtxFlag0Clear;
    table->update = func_ov038_020ba66c;
    table->setMode = SetSoundCtxMode;
    table->hasObject = HasOv038ObjectField28;
    table->release = ReleaseOv038Object;
    table->pause = func_ov038_020ba6f8;
    table->resume = func_ov038_020ba700;
}
