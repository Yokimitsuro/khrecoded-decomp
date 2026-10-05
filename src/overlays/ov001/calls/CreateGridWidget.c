#include "nitro/types.h"

typedef void (*GridCallback)(void);

typedef struct GridObject {
    GridCallback onInit;
    GridCallback onDestroy;
    GridCallback onUpdate;
    GridCallback onDraw;
    GridCallback onEnter;
    GridCallback unused14;
    GridCallback onLeave;
    GridCallback handler1c;
    GridCallback onTouch;
    GridCallback onRelease;
    GridCallback onDrag;
    GridCallback onSelect;
    GridCallback onCancel;
    GridCallback handler34;
    GridCallback handler38;
    GridCallback onFinish;
    u8 pad_40[0xc];
    int target;
    int depth;
    u8 pad_54[0x10];
    u16 priority;
    u8 pad_66[0xa];
    int color;
    int offsetX;
    int offsetY;
    u8 layer;
    u8 slotCount;
    u8 pad_7e[4];
    u8 group;
    u8 pad_83;
    u8 state;
    s8 selection;
    s16 hoverId;
    int value;
    u8 pad_8c[4];
    u16 counter;
} GridObject;

extern GridObject *CreateByteGrid(int headerSize, int width, int height);
extern void AcquireEffectRecordPair(void);
extern void FieldObject_EnsureModelsLoaded(void);
extern void RespawnContactFieldObject(void);
extern void func_ov001_0207f210(void);
extern void FieldObject_ReleaseGroupAndClose(void);
extern void func_ov001_02084d84(void);
extern void func_ov001_02084dcc(void);
extern void GetFieldOffset40_02084dd0(void);
extern void MoveLinkedActor(void);
extern void GetWorkFieldOffset50_02084e08(void);
extern void FieldObject_CollideSweptShape(void);
extern void DrawActorWithShadow_02085b90(void);

GridObject *CreateGridWidget(int height, int *value)
{
    GridObject *grid = CreateByteGrid(0x94, 0xd0, height);

    grid->state = 0;
    grid->selection = -1;
    grid->depth = 0x10;
    grid->layer = 2;
    grid->color = 0x14cd;
    grid->offsetX = 0;
    grid->offsetY = 0;
    grid->priority = 0x7d;
    grid->group = 0xff;
    grid->target = -1;
    grid->onInit = AcquireEffectRecordPair;
    grid->onDestroy = FieldObject_EnsureModelsLoaded;
    grid->onUpdate = RespawnContactFieldObject;
    grid->onDraw = func_ov001_0207f210;
    grid->onEnter = FieldObject_ReleaseGroupAndClose;
    grid->onLeave = func_ov001_02084d84;
    grid->handler1c = NULL;
    grid->onTouch = func_ov001_02084dcc;
    grid->onDrag = GetFieldOffset40_02084dd0;
    grid->onRelease = MoveLinkedActor;
    grid->onSelect = GetWorkFieldOffset50_02084e08;
    grid->handler38 = NULL;
    grid->onCancel = FieldObject_CollideSweptShape;
    grid->handler34 = NULL;
    grid->onFinish = DrawActorWithShadow_02085b90;
    grid->slotCount = 10;
    grid->hoverId = -1;
    grid->counter = 0;
    grid->value = *value;
    return grid;
}
