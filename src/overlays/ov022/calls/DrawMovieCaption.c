#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x830];
    u8 textLayer[0x50];
    int captionDirty;
    u8 pad_884[0x38];
    int hasCaption;
    u8 topLayout[0x100];
    u8 bottomLayout[0x100];
} MoviePlayer;

extern MoviePlayer *data_ov022_020b7da0;
extern const char *gStreamBufferTables[];

extern void ResetSubtitleLine(void *stream);
extern void func_ov022_020a9118(void *stream, void *layout);
extern u32 GetLanguageIndex(void);
extern int Utf8ToUcs2(const char *src, u16 *dst, int maxChars);
extern void DrawTextAnchored(void *window, int x, int y, int color, int flags, const void *text);
extern void UploadDirtySubtitleTiles(void *stream);

void DrawMovieCaption(BOOL top) {
    MoviePlayer *player = data_ov022_020b7da0;
    void *layout = top ? player->topLayout : player->bottomLayout;
    u16 text[0x40];

    ResetSubtitleLine(player->textLayer);
    func_ov022_020a9118(player->textLayer, layout);
    if (player->hasCaption) {
        u32 language = GetLanguageIndex();

        player->captionDirty = 0;
        Utf8ToUcs2(gStreamBufferTables[language], text, 0x40);
        DrawTextAnchored(player->textLayer, 0xfd, 3, 1, 0x20, text);
    }
    UploadDirtySubtitleTiles(player->textLayer);
}
