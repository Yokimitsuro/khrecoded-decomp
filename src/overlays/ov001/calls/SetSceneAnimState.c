#include "nitro/types.h"

typedef struct {
    u32 ids[3];
} AnimIdTable;

typedef struct {
    u8 pad_000[0x1c];
    u8 animPool[0x1fc - 0x1c];
    int animState;
} Scene;

typedef struct {
    u32 unk0;
    Scene *scene;
} SceneHolder;

extern SceneHolder data_ov001_020a04c4;
extern const AnimIdTable data_ov001_0209dc04;
extern void *FindActiveRecordById(void *pool, u16 recordId);
extern void func_ov027_020b8230(void *pool, void *record);
extern void func_ov027_020b8288(void *pool, void *record);

void SetSceneAnimState(int state)
{
    Scene *scene = data_ov001_020a04c4.scene;
    AnimIdTable table = data_ov001_0209dc04;
    void *pool = scene->animPool;

    if (state != scene->animState) {
        scene->animState = state;
        if (state <= -1) {
            func_ov027_020b8288(pool, FindActiveRecordById(pool, table.ids[0]));
            return;
        }
        func_ov027_020b8230(pool, FindActiveRecordById(pool, table.ids[state]));
    }
}
