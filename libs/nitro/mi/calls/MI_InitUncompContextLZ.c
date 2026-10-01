#include "libs/nitro/mi/mi_uncomp_stream_internal.h"

void MI_InitUncompContextLZ(
    MIUncompContextLZ *context, u8 *dest,
    const MICompressionHeader *header)
{
    context->destp = dest;
    context->destCount = (s32)header->destSize;
    context->flags = 0;
    context->flagIndex = 0;
    context->length = 0;
    context->lengthFlg = 3;
    context->destTmp = 0;
    context->destTmpCnt = 0;
    context->exFormat = (u8)((header->compParam == 0) ? 0U : 1U);
}
