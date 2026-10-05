#include "nitro/types.h"

typedef struct BannedWord {
    s32 size;
    u16 chars[1];
} BannedWord;

typedef struct MessageFile {
    void *file;
    u32 unk_04;
    BannedWord *words;
} MessageFile;

extern int GetWideStringLength(const u16 *text);
extern MessageFile *func_ov002_02062ca4(void);
extern s16 GetLanguageIndex(void);
extern BOOL MatchWideTextPattern(const u16 *text, const u16 *word, int length);

BOOL CensorBannedWords(u16 *out, void *unused, const u16 *text)
{
    int entryIndex;
    BOOL censored;
    int entryCount;
    int textLength;
    BannedWord *entry;

    censored = entryIndex = 0;
    textLength = GetWideStringLength(text);
    entry = func_ov002_02062ca4()->words;
    if (GetLanguageIndex() == 0) {
        entryCount = 0xfc;
    } else {
        entryCount = 0x940;
    }
    do {
        const u16 *word;
        u16 *dst;
        const u16 *src;
        int entrySize;
        int byteLength;
        int wordLength;

        entrySize = entry->size;
        byteLength = entrySize - 6;
        wordLength = byteLength / sizeof(u16);
        word = entry->chars;

        for (dst = out, src = text; dst - out < textLength - wordLength + 1; dst++, src++) {
            if (byteLength > 0 && MatchWideTextPattern(src, word, wordLength)) {
                int i;

                for (i = 0; i < wordLength; i++) {
                    if (word[i] != '$') {
                        dst[i] = '?';
                    }
                }
                censored = TRUE;
                dst += wordLength - 1;
                src += wordLength - 1;
            }
        }
        entryIndex++;
        entry = (BannedWord *)((u8 *)entry + entrySize);
    } while (entryIndex < entryCount);
    return censored;
}
