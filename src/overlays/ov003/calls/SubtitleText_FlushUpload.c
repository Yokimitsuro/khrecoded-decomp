#include "nitro/types.h"

typedef struct SubtitleTextRenderer {
    u8 pad_00[0x44];
    BOOL uploadPending;
} SubtitleTextRenderer;

extern void Text_UploadTileBuffer(SubtitleTextRenderer *renderer);

void SubtitleText_FlushUpload(SubtitleTextRenderer *renderer)
{
    if (!renderer->uploadPending) {
        return;
    }
    Text_UploadTileBuffer(renderer);
    renderer->uploadPending = FALSE;
}
