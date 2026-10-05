#include "nitro/types.h"

typedef void (*AnmFunc)(void *result, const void *anmObj, u32 dataIdx);

typedef struct AnmObj {
    u32 frame;
    u32 ratio;
    void *resAnm;
    AnmFunc funcAnm;
    struct AnmObj *next;
} AnmObj;

typedef struct AnimTarget {
    u8 pad_00[4];
    s16 slotCount;
    u8 pad_06[0x12];
    AnmObj **slots;
} AnimTarget;

extern void NNSi_G3dAnmCalcNsBma(void *result, const void *anmObj, u32 dataIdx);
extern void CalcMaterialAnimWithGlobalAlpha(void *result, const void *anmObj, u32 dataIdx);

void HookMaterialAnimAlpha(AnimTarget *target)
{
    int i;
    AnmObj *anm;

    if (target->slotCount != 0 && target->slots != NULL) {
        for (i = 0; i < target->slotCount; i++) {
            for (anm = target->slots[i]; anm != NULL; anm = anm->next) {
                if (anm->funcAnm == NNSi_G3dAnmCalcNsBma) {
                    anm->funcAnm = CalcMaterialAnimWithGlobalAlpha;
                }
            }
        }
    }
}
