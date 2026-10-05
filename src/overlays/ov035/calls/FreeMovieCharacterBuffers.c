#include "nitro/types.h"

typedef struct CharacterValues {
    u8 pad_00[0x10];
    void *entries;
    u8 pad_14[0x10];
    void *names;
    void *icons;
    void *values;
} CharacterValues;

typedef struct MovieContext {
    u8 pad_00[0x40];
    CharacterValues characters;
} MovieContext;

extern MovieContext *data_ov035_020bc500;
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void FreeMovieCharacterBuffers(void)
{
    MovieContext *context = data_ov035_020bc500;
    CharacterValues *characters = &context->characters;

    if (context->characters.entries != NULL) {
        NNSi_FndFreeFromDefaultHeap(context->characters.entries);
        context->characters.entries = NULL;
    }
    if (characters->names != NULL) {
        NNSi_FndFreeFromDefaultHeap(characters->names);
        characters->names = NULL;
    }
    if (characters->icons != NULL) {
        NNSi_FndFreeFromDefaultHeap(characters->icons);
        characters->icons = NULL;
    }
    if (characters->values != NULL) {
        NNSi_FndFreeFromDefaultHeap(characters->values);
        characters->values = NULL;
    }
}