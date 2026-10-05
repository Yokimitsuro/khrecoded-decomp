#include "nitro/types.h"

typedef struct ManagedObject ManagedObject;

struct ManagedObject {
    u8 pad_000[0x200];
    void (*update)(ManagedObject *object, int arg);
};

typedef struct ManagerEntry {
    u32 unk_00;
    ManagedObject *object;
    u8 pad_08[0x20];
} ManagerEntry;

typedef struct FieldManager {
    u32 unk_00;
    ManagerEntry entries[3];
    int entryCount;
} FieldManager;

extern FieldManager *data_ov001_020a04bc;

void NotifyManagerEntryObjects(void)
{
    FieldManager *manager = data_ov001_020a04bc;
    int entryIndex;

    if (manager != NULL) {
        for (entryIndex = 0; entryIndex < manager->entryCount; entryIndex++) {
            ManagedObject *object = manager->entries[entryIndex].object;
            if (object != NULL && object->update != NULL) {
                object->update(object, 0);
            }
        }
    }
}
