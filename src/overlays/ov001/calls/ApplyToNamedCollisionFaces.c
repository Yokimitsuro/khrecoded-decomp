#include "nitro/types.h"

typedef struct CollModel CollModel;

typedef struct CollModelSet {
    u16 pad_00;
    u16 modelCount;
    CollModel **models;
} CollModelSet;

typedef void (*CollFaceCallback)(CollModel *model, void *face, void *arg);

extern CollModelSet *GetActorRegistry(void);
extern char *func_ov001_020670b4(CollModel *model, const char *name, int nameLength, int *searchIndex);
extern void ForEachFaceOnPoint(CollModel *model, u8 kindMask, char *point, CollFaceCallback callback, void *arg);
extern void SetMeshEnabled(CollModel *model, void *face, void *arg);

void ApplyToNamedCollisionFaces(const char *name, int nameLength, void *arg)
{
    int i;
    CollModelSet *set = GetActorRegistry();

    for (i = 0; i < set->modelCount; i++) {
        CollModel *model = set->models[i];
        char *entry;
        int cursor;

        for (cursor = 0;; cursor++) {
            entry = func_ov001_020670b4(model, name, nameLength, &cursor);
            if (entry == NULL) {
                break;
            }
            ForEachFaceOnPoint(model, 2, entry, SetMeshEnabled, arg);
            ForEachFaceOnPoint(model, 1, entry, SetMeshEnabled, arg);
            ForEachFaceOnPoint(model, 4, entry, SetMeshEnabled, arg);
        }
    }
}
