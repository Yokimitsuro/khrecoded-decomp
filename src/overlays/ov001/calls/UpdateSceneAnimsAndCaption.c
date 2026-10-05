#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SceneEntry {
    u8 unk00;
    u8 regionCount;
} SceneEntry;

typedef struct SceneTableFile {
    u8 count;
    u8 pad_01[7];
    SceneEntry *entries[1];
} SceneTableFile;

typedef struct CaptionRegion {
    VecFx32 min;
    VecFx32 max;
    int captionId;
    void *enabled;
    u8 pad_20[2];
    u16 flags;
} CaptionRegion;

typedef struct SceneAnim {
    u8 tracks[0x104];
    u8 flags;
    u8 pad_105[3];
} SceneAnim;

typedef struct SceneContext {
    SceneTableFile *table;
    u8 pad_04[9];
    s8 currentId;
    u8 pad_0e;
    u8 flags;
    u8 pad_10[4];
    CaptionRegion *regions;
    SceneAnim anims[16];
    u8 pad_1098[0x38];
    void (*onUpdate)(void *arg, struct SceneContext *context, fx32 delta);
    u8 hookArg[4];
} SceneContext;

extern SceneContext *data_ov001_020a048c;
extern u16 AdvanceAnimationTracks(SceneAnim *anim, fx32 delta);
extern int func_0202f4cc(SceneAnim *anim, u16 track);
extern void func_01ffb2f8(SceneAnim *anim, u16 track, fx32 frame);
extern void Flags16_SetBit1(SceneAnim *anim);
extern int func_ov001_020644b0(void);
extern int func_ov001_0206dc38(void);
extern VecFx32 *func_ov001_0206dc4c(int index);
extern void SetFieldCaptionText(int captionId);

void UpdateSceneAnimsAndCaption(fx32 delta)
{
    SceneContext *context = data_ov001_020a048c;
    CaptionRegion *regions;
    int count;
    CaptionRegion *region;
    VecFx32 *position;
    u16 mask;
    int track;
    SceneAnim *anim;
    int i;
    int captionId;

    if (context->onUpdate != NULL) {
        context->onUpdate(context->hookArg, context, delta);
    }
    for (i = 0; i < 16; i++) {
        anim = &context->anims[i];
        if (anim->flags & 0x80) {
            mask = AdvanceAnimationTracks(anim, delta);
            if ((anim->flags & 2) && mask != 0) {
                for (track = 0; track < 5; track++) {
                    if (mask & 1) {
                        func_01ffb2f8(anim, track, func_0202f4cc(anim, track) - 0x1000);
                        mask >>= 1;
                    }
                }
                Flags16_SetBit1(anim);
                anim->flags |= 4;
            }
        }
    }
    if (!(context->flags & 2) && func_ov001_020644b0() != 900) {
        captionId = 0;
        if (context->regions != NULL && func_ov001_0206dc38() > 0) {
            position = func_ov001_0206dc4c(captionId);
            count = context->table->entries[context->currentId]->regionCount;
            i = captionId;
            if (i < count) {
                regions = context->regions;
                do {
                    region = &regions[i];
                    if (region->enabled != NULL && (region->flags & 1) && region->min.x <= position->x
                        && region->min.y <= position->y && region->min.z <= position->z
                        && region->max.x >= position->x && region->max.y >= position->y
                        && region->max.z >= position->z) {
                        captionId = region->captionId;
                        break;
                    }
                    i++;
                } while (i < count);
            }
        }
        SetFieldCaptionText(captionId);
    }
}
