#include "nitro/types.h"

typedef struct CharacterEntry {
    u8 id;
    u8 pad_01[3];
} CharacterEntry;

typedef struct CharacterTable {
    u8 count;
    u8 pad_01[3];
    CharacterEntry *entries;
} CharacterTable;

typedef struct CharacterSource {
    u8 pad_00[4];
    CharacterTable *table;
} CharacterSource;

typedef struct CharacterValues {
    u8 pad_00[0x2c];
    u8 *values;
} CharacterValues;

typedef struct MovieContext {
    u8 pad_00[0x38];
    CharacterSource *source;
    u8 pad_3c[4];
    CharacterValues characters;
} MovieContext;

extern MovieContext *data_ov035_020bc500;

u8 LookupMovieCharacterValue(int id)
{
    int i;
    CharacterValues *characters = &data_ov035_020bc500->characters;
    CharacterTable *table = data_ov035_020bc500->source->table;

    for (i = 0; i < table->count; i++) {
        if (id == table->entries[i].id) {
            return characters->values[i];
        }
    }
    return 0x28;
}