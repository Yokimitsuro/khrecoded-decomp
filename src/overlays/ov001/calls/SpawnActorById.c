#include "nitro/types.h"

typedef struct {
    u16 owner;
    u16 actorId;
    u16 variant;
    u8 pad[10];
} SpawnDesc;

extern void func_01ff88c4(void *dst, u32 value, u32 size);
extern int func_ov001_02096b08(int linkOwner, SpawnDesc *desc, void *position);

int SpawnActorById(int linkOwner, int id, int variant) {
    SpawnDesc desc;
    func_01ff88c4(&desc, 0, sizeof(SpawnDesc));
    if (id == 0) {
        return 0;
    }
    desc.actorId = id;
    desc.variant = variant;
    return func_ov001_02096b08(linkOwner, &desc, NULL);
}
