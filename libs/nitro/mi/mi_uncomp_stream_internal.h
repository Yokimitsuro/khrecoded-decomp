#ifndef NITRO_MI_UNCOMP_STREAM_INTERNAL_H
#define NITRO_MI_UNCOMP_STREAM_INTERNAL_H

#include "libs/nitro/os/os_types_internal.h"

typedef struct MICompressionHeader {
    u32 compParam : 4;
    u32 compType : 4;
    u32 destSize : 24;
} MICompressionHeader;

typedef struct MIUncompContextLZ {
    u8 *destp;
    s32 destCount;
    u32 length;
    u16 destTmp;
    u8 destTmpCnt;
    u8 flags;
    u8 flagIndex;
    u8 lengthFlg;
    u8 exFormat;
    u8 padding;
} MIUncompContextLZ;

void MI_InitUncompContextLZ(
    MIUncompContextLZ *context, u8 *dest,
    const MICompressionHeader *header);
s32 MI_ReadUncompLZ8(
    MIUncompContextLZ *context, const u8 *data, u32 length);

#endif
