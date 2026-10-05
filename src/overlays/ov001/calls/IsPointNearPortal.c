#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SceneObjectDef {
    u8 pad_00[0x7d];
    u8 type;
} SceneObjectDef;

typedef struct SceneObject SceneObject;

struct SceneObject {
    u32 unk_00;
    SceneObject *next;
    SceneObjectDef *def;
};

extern SceneObject *func_ov001_0207f0b4(void);
extern BOOL SceneObject_IsPointWithinOneUnit(SceneObject *object, const VecFx32 *point);

BOOL IsPointNearPortal(const VecFx32 *point)
{
    SceneObject *object;

    for (object = func_ov001_0207f0b4(); object != NULL; object = object->next) {
        if (object->def->type == 2 && SceneObject_IsPointWithinOneUnit(object, point)) {
            return TRUE;
        }
    }
    return FALSE;
}
