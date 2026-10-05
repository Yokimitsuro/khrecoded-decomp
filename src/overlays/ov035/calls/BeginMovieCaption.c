#include "nitro/types.h"

typedef struct CaptionParams {
    s8 style;
    s8 line;
    s16 x;
    s16 y;
} CaptionParams;

typedef struct MovieContext {
    s16 line;
    s16 x;
    s16 y;
    u16 flags;
    u8 pad_08[0x10];
    int timer;
    s8 style;
} MovieContext;

extern MovieContext *data_ov035_020bc500;

void BeginMovieCaption(CaptionParams *params)
{
    data_ov035_020bc500->x = params->x;
    data_ov035_020bc500->y = params->y;
    data_ov035_020bc500->line = params->line;
    data_ov035_020bc500->flags = 3;
    data_ov035_020bc500->flags |= 0x20;
    data_ov035_020bc500->style = params->style;
    data_ov035_020bc500->timer = 0;
}