#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptEntityParams {
    s32 entityId;
    s32 groupId;
    u16 extraLow;
    u8 extraHigh;
    u8 flagByte;
    u32 kindHigh;
    u32 kind;
    s32 kindParam;
    fx32 posX;
    fx32 posY;
    fx32 posZ;
    fx32 radius;
    s16 linkA;
    s16 linkB;
    s16 linkC;
    s16 linkD;
    s32 linkId;
    u8 enableA;
    u8 enableB;
    u8 enableC;
    u8 attrByte;
    u32 flagLow : 1;
    u32 flagHigh : 1;
    u32 modelId : 10;
    u32 motionId : 10;
    u32 effectId : 10;
    u8 pad_3c[4];
    fx32 rangeMin;
    fx32 rangeMax;
    fx32 height;
    u32 soundId : 10;
    u32 soundParam : 12;
    u32 unk_4c_22 : 10;
    u8 pad_50[0x5c - 0x50];
} ScriptEntityParams;

extern void func_01ff88c4(void *dst, u32 value, u32 size);


void InitScriptEntityParams(ScriptEntityParams *params)
{
    func_01ff88c4(params, 0, sizeof(ScriptEntityParams));
    params->extraLow = 0xffff;
    params->extraHigh = 0xff;
    params->linkB = -1;
    params->linkA = -1;
    params->kindParam = -1;
    params->linkId = -1;
    params->linkC = -1;
    params->linkD = -1;
    params->enableA = 1;
    params->enableB = 1;
    params->enableC = 1;
    params->soundParam = 0xfff;
    params->flagLow = 0;
}
