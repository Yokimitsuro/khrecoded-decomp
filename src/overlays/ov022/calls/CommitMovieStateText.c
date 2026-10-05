#include "nitro/types.h"

typedef struct MovieOverlayState {
    u8 pad_000[0x8b5];
    u8 textVisible;
    u8 pad_8b6[0x8c0 - 0x8b6];
    char currentText[0x100];
    char savedText[0x100];
} MovieOverlayState;

extern MovieOverlayState *data_ov022_020b7da0;
extern char *strcpy(char *dst, const char *src);
extern void DrawMovieCaption(BOOL useCurrentText);

void CommitMovieStateText(void)
{
    strcpy(data_ov022_020b7da0->savedText, data_ov022_020b7da0->currentText);
    DrawMovieCaption(TRUE);
    data_ov022_020b7da0->textVisible = TRUE;
}
