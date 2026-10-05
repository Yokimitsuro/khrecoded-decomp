#include "nitro/types.h"

typedef struct LangPath {
    s16 language;
    s16 pad_02;
    char *buffer;
} LangPath;

extern LangPath gLanguagePath;

s16 GetLanguageIndex(void)
{
    return gLanguagePath.language;
}
