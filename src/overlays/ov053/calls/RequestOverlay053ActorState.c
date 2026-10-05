#include "nitro/types.h"

typedef struct Entity {
    u8 pad_000[0x75c];
    int currentState;
    u8 pad_760[0x764 - 0x760];
    void *blendTable;
    u8 pad_768[0x850 - 0x768];
    u8 defaultBlend[0x9ac - 0x850];
    u64 stateFlags;
} Entity;

extern BOOL func_ov001_020645c8(u32 value);
extern void func_ov052_020ce0e0(Entity *entity, void *blendTable, int state, int blendIndex, int frames);
extern void func_ov052_020cde40(Entity *entity, int state, int frames);

void RequestOverlay053ActorState(Entity *entity, int state, int frames)
{
    void *defaultBlend = entity->defaultBlend;
    int blendIndex;

    if ((entity->stateFlags & 0x40) == 0 || func_ov001_020645c8(0x3520)) {
        blendIndex = -1;
        if (!func_ov001_020645c8(0x3609) && !func_ov001_020645c8(0x360a) && !func_ov001_020645c8(0x360b)) {
            switch (state) {
            case 0:
                blendIndex = 0;
                break;
            case 1:
                blendIndex = 1;
                break;
            }
        } else {
            switch (state) {
            case 0:
                blendIndex = 0;
                break;
            case 1:
                blendIndex = 1;
                break;
            case 2:
                blendIndex = 2;
                break;
            case 10:
                blendIndex = 3;
                break;
            case 3:
                blendIndex = 4;
                break;
            case 4:
                blendIndex = 5;
                break;
            case 5:
                blendIndex = 6;
                break;
            case 0x1e:
                blendIndex = 11;
                break;
            case 6:
                blendIndex = 7;
                break;
            case 7:
                blendIndex = 8;
                break;
            case 8:
                blendIndex = 9;
                break;
            case 9:
                blendIndex = 10;
                break;
            }
        }
        if (blendIndex != -1) {
            if (state == entity->currentState) {
                return;
            }
            func_ov052_020ce0e0(entity, defaultBlend, state, blendIndex, frames);
            return;
        }
    } else if (defaultBlend == entity->blendTable) {
        entity->currentState = -1;
    }
    func_ov052_020cde40(entity, state, frames);
}
