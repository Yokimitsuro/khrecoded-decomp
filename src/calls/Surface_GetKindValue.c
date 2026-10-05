#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SurfaceSource {
    u8 pad_00[0x0c];
    fx32 unk_0C;
    u8 pad_10[0x18];
    fx32 unk_28;
} SurfaceSource;

typedef struct Surface {
    u8 pad_00[0x24];
    SurfaceSource *source;
    u8 pad_28[0x18];
    s32 kind;
} Surface;

fx32 Surface_GetKindValue(Surface *surface)
{
    switch (surface->kind) {
    case 0:
        return surface->source->unk_0C;
    case 1:
        return surface->source->unk_0C;
    case 3:
    case 4:
        return surface->source->unk_28;
    }
    return 0;
}
