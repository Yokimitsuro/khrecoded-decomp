#include "nitro/types.h"

typedef struct CueDef {
    s16 id;
    s16 handlerType;
} CueDef;

typedef struct CueTable {
    u8 pad0[0xc];
    void *context;
} CueTable;

typedef struct CueInstance {
    u8 pad0[0xc];
    s16 *source;
} CueInstance;

typedef CueInstance *(*CueFactory)(void *owner, void *arg, CueDef *def, void *context);

typedef struct CueFactoryTable {
    CueFactory factories[7];
} CueFactoryTable;

extern const CueFactoryTable gEffectCreationHandlers;
extern CueDef *FindWideEntryById(CueTable *table, int id);
extern int func_ov001_02063a38(void);

CueInstance *SpawnCueHandler(s16 *source, void *owner, void *arg, CueTable *table)
{
    CueDef *def;
    CueFactoryTable factories;
    CueInstance *instance;
    BOOL blocked = FALSE;

    def = FindWideEntryById(table, *source);

    if (def == NULL) {
        return NULL;
    }
    factories = gEffectCreationHandlers;
    if (func_ov001_02063a38() == 6) {
        if (def->id != 0xb7 && def->id != 0xb8) {
            blocked = TRUE;
        }
        if (blocked) {
            return NULL;
        }
    }
    instance = factories.factories[def->handlerType](owner, arg, def, table->context);
    if (instance != NULL) {
        instance->source = source;
    }
    return instance;
}
