#include "nitro/types.h"

typedef struct FieldDef {
    u8 pad_00[0x5a];
    u8 kind;
} FieldDef;

extern int func_ov001_02087270(void);
extern FieldDef *func_ov001_0208723c(int index);

FieldDef *FindKind4FieldObject(void)
{
    int i;
    int count;
    FieldDef *def;

    count = func_ov001_02087270();
    for (i = 0; i < count; i++) {
        def = func_ov001_0208723c(i);
        if (def->kind == 4) {
            return def;
        }
    }
    return NULL;
}
