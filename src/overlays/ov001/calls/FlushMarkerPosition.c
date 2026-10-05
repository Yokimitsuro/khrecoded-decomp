#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u16 active;
    u16 state;
    u16 kind;
    u16 id;
    VecFx32 position;
    u8 pad_14[0x28 - 0x14];
} MarkerEntry;

typedef struct {
    u32 flags;
    u8 pad_00004[0x18814 - 0x4];
    MarkerEntry markers[16];
} MarkerManager;

typedef struct {
    u8 pad_00[0x76];
    s8 busy;
} MarkerTarget;

typedef struct {
    VecFx32 offset;
    u8 mode;
    u8 flag;
    u8 pad_0e[6];
    u32 unk_14;
    u32 unk_18;
} MarkerUpdate;

extern MarkerManager *data_ov001_020a0528;
extern VecFx32 data_0205344c;

extern MarkerTarget *func_ov001_0208724c(u32 kind, u32 id);
extern BOOL func_ov016_020a6a98(MarkerTarget *target);
extern void func_01ff88c4(void *dst, u32 value, u32 size);
extern void func_ov001_02086408(MarkerTarget *target, MarkerUpdate *update);

void FlushMarkerPosition(u16 id) {
    MarkerManager *manager = data_ov001_020a0528;
    int i;

    if (manager->flags & 0x10000) {
        return;
    }
    for (i = 0; i < 16; i++) {
        MarkerEntry *entry = &manager->markers[i];
        if (entry->id == id + 1) {
            MarkerTarget *target = func_ov001_0208724c(entry->kind, entry->id - 1);
            MarkerUpdate update;
            BOOL claimed;

            if (target == NULL) {
                return;
            }
            if (func_ov016_020a6a98(target)) {
                return;
            }
            claimed = FALSE;
            func_01ff88c4(&update, 0, sizeof(update));
            update.offset = data_0205344c;
            update.mode = 0xff;
            update.flag = 0;
            update.unk_14 = 0;
            update.unk_18 = 0;
            if (target->busy == 0) {
                claimed = TRUE;
                target->busy = 1;
            }
            do {
                func_ov001_02086408(target, &update);
            } while (!func_ov016_020a6a98(target));
            if (claimed == TRUE) {
                target->busy = 0;
            }
            entry->state = 2;
            return;
        }
    }
}
