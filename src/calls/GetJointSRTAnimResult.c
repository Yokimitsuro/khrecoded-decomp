#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct JointAnimResult {
    u32 flag;
    VecFx32 scale;
    VecFx32 scaleEx0;
    VecFx32 scaleEx1;
    MtxFx33 rot;
    VecFx32 trans;
} JointAnimResult;

typedef struct JointAnimResource {
    u8 category0;
    u8 revision;
    u16 category1;
    u16 numFrame;
    u16 numNode;
    u32 flag;
    u32 ofsRot3;
    u32 ofsRot5;
} JointAnimResource;

typedef struct JointAnimSRTTag {
    u32 tag;
} JointAnimSRTTag;

extern void ModelAnimation_SampleJointTranslation(fx32 *value, fx32 frame, const u32 *data,
                          const JointAnimResource *jointAnim);
extern void ModelAnimation_ApplyDefaultJointPosition(JointAnimResult *result);
extern void SampleJointRotationStreamITCM(MtxFx33 *rot, fx32 frame, const u32 *data,
                          const JointAnimResource *jointAnim);
extern BOOL DecodeCompressedRotationITCM(MtxFx33 *rot, const void *rot3Array,
                          const void *rot5Array, u32 info);
extern void NNSi_G3dGetMdlRot(JointAnimResult *result);
extern void ModelAnimation_SampleJointScale(fx32 *values, fx32 frame, const u32 *data,
                          const JointAnimResource *jointAnim);
extern void ModelAnimation_ApplyDefaultJointScale(JointAnimResult *result);

static inline void CrossProduct(const VecFx32 *a, const VecFx32 *b, VecFx32 *axb)
{
    axb->x = (a->y * b->z - a->z * b->y) >> 12;
    axb->y = (a->z * b->x - a->x * b->z) >> 12;
    axb->z = (a->x * b->y - a->y * b->x) >> 12;
}

void GetJointSRTAnimResult(const JointAnimResource *jointAnim,
                                    JointAnimSRTTag *srtTag,
                                    u32 tag, fx32 frame, JointAnimResult *result,
                                    fx32 *scaleAndInverse)
{
    u32 *data = (u32 *)((u8 *)srtTag + sizeof(JointAnimSRTTag));

    if (!(tag & (0x2 | 0x4))) {
        if (!(tag & 0x8)) {
            ModelAnimation_SampleJointTranslation(&result->trans.x, frame, data, jointAnim);
            data += 2;
        } else {
            result->trans.x = *(const fx32 *)data;
            data += 1;
        }

        if (!(tag & 0x10)) {
            ModelAnimation_SampleJointTranslation(&result->trans.y, frame, data, jointAnim);
            data += 2;
        } else {
            result->trans.y = *(const fx32 *)data;
            data += 1;
        }

        if (!(tag & 0x20)) {
            ModelAnimation_SampleJointTranslation(&result->trans.z, frame, data, jointAnim);
            data += 2;
        } else {
            result->trans.z = *(const fx32 *)data;
            data += 1;
        }
    } else {
        if (tag & 0x2) {
            result->flag |= 0x4;
        } else {
            ModelAnimation_ApplyDefaultJointPosition(result);
        }
    }

    if (!(tag & (0x40 | 0x80))) {
        if (!(tag & 0x100)) {
            SampleJointRotationStreamITCM(&result->rot, frame, data, jointAnim);
            data += 2;
        } else {
            if (DecodeCompressedRotationITCM(&result->rot,
                              (const u8 *)jointAnim + jointAnim->ofsRot3,
                              (const u8 *)jointAnim + jointAnim->ofsRot5,
                              *data)) {
                CrossProduct((const VecFx32 *)&result->rot._00,
                             (const VecFx32 *)&result->rot._10,
                             (VecFx32 *)&result->rot._20);
            }
            data += 1;
        }
    } else {
        if (tag & 0x40) {
            result->flag |= 0x2;
        } else {
            NNSi_G3dGetMdlRot(result);
        }
    }

    if (!(tag & (0x200 | 0x400))) {
        if (!(tag & 0x800)) {
            fx32 scaleX[2];
            ModelAnimation_SampleJointScale(&scaleX[0], frame, data, jointAnim);
            scaleAndInverse[0] = scaleX[0];
            scaleAndInverse[3] = scaleX[1];
        } else {
            const fx32 *values = (const fx32 *)data;
            scaleAndInverse[0] = values[0];
            scaleAndInverse[3] = values[1];
        }
        data += 2;

        if (!(tag & 0x1000)) {
            fx32 scaleY[2];
            ModelAnimation_SampleJointScale(&scaleY[0], frame, data, jointAnim);
            scaleAndInverse[1] = scaleY[0];
            scaleAndInverse[4] = scaleY[1];
        } else {
            const fx32 *values = (const fx32 *)data;
            scaleAndInverse[1] = values[0];
            scaleAndInverse[4] = values[1];
        }
        data += 2;

        if (!(tag & 0x2000)) {
            fx32 scaleZ[2];
            ModelAnimation_SampleJointScale(&scaleZ[0], frame, data, jointAnim);
            scaleAndInverse[2] = scaleZ[0];
            scaleAndInverse[5] = scaleZ[1];
        } else {
            const fx32 *values = (const fx32 *)data;
            scaleAndInverse[2] = values[0];
            scaleAndInverse[5] = values[1];
        }
    } else {
        if (tag & 0x200) {
            result->flag |= 0x1;
        } else {
            ModelAnimation_ApplyDefaultJointScale(result);
        }
    }
}
