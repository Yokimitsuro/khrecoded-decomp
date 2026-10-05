#include "nitro/types.h"

extern void *data_ov022_020b7da0;
extern char *strcpy(char *dst, const char *src);

void SetMovieStateText(const char *text)
{
    strcpy((char *)data_ov022_020b7da0 + 0x8c0, text);
}
