#include "nitro/types.h"

typedef struct LangPath {
    s16 lang;
    s16 pad02;
    char *buf;
} LangPath;

extern LangPath data_0206055c;
extern const char *gLanguageCodeTable[];

char *Msg_BuildLangPath(const char *src)
{
    char *dst = data_0206055c.buf;
    const char *p = gLanguageCodeTable[data_0206055c.lang];

    while (*src != 0) {
        char c = *(const volatile char *)src;

        switch (c) {
        case '&':
            src++;
            dst[0] = p[0];
            dst[1] = *++p;
            dst += 2;
            break;
        default:
            src++;
            *dst++ = c;
            break;
        }
    }
    *dst = 0;
    return data_0206055c.buf;
}
