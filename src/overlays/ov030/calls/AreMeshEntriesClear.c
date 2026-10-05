#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x80];
    u8 meshIds[4];
} MeshSlotTable;

typedef struct {
    MeshSlotTable *table;
    int mode;
} MeshCheckState;

extern u8 *GetWorldMeshNamedEntry(int index);
extern BOOL func_ov001_020681e8(u8 *entry, u32 kind);

BOOL AreMeshEntriesClear(MeshCheckState *state)
{
    BOOL result = TRUE;
    u8 *entry;
    int i;

    switch (state->mode) {
    case 2:
    case 3:
        for (i = 0; i < 4; i++) {
            entry = GetWorldMeshNamedEntry(state->table->meshIds[i]);
            if (entry != NULL && func_ov001_020681e8(entry, 10)) {
                result = FALSE;
                break;
            }
        }
        break;
    case 1:
        for (i = 0; i < 4; i++) {
            entry = GetWorldMeshNamedEntry(state->table->meshIds[i]);
            if (entry != NULL && func_ov001_020681e8(entry, 10)) {
                result = FALSE;
                break;
            }
        }
        break;
    }
    return result;
}
