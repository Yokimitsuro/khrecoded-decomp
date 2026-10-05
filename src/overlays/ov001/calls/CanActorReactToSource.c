#include "nitro/types.h"

typedef struct ReactSelf {
    u8 pad[0xc];
    u8 flags;
} ReactSelf;

typedef struct ReactSource {
    int unk0;
    int kind;
} ReactSource;

typedef struct ReactActor {
    u8 pad[0x26c];
    u32 stateFlags : 31;
    u32 unk26c : 1;
    u8 pad270[0x18];
    u16 unk288 : 2;
    u16 stance : 2;
    u16 unk288b : 12;
} ReactActor;

BOOL CanActorReactToSource(ReactSelf *self, ReactSource *source, ReactActor *actor) {
    if (actor->stateFlags & 0x800) {
        return FALSE;
    }
    if (self->flags & 2) {
        return FALSE;
    }
    if (source == NULL) {
        return TRUE;
    }
    if (actor->stance != 1) {
        return TRUE;
    }
    if (source->kind == 1) {
        return FALSE;
    }
    if (source->kind != 2) {
        return TRUE;
    }
    return FALSE;
}
