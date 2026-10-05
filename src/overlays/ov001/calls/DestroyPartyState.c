#include "nitro/types.h"

typedef struct PartyActor {
    u8 pad_000[0x1e0];
    void (*destroy)(struct PartyActor *actor);
} PartyActor;

typedef struct PartyEntry {
    int overlayId;
    PartyActor *actor;
    u8 pad_08[0x1c];
    u16 flags;
    u8 pad_26[2];
} PartyEntry;

typedef struct PartyState {
    int selected;
    PartyEntry entries[3];
    int count;
    int handles[3];
    int unk_08c;
    void *gauge;
    u8 pad_094[0x68];
    u8 *buffers;
} PartyState;

extern PartyState *data_ov001_020a04bc;
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void UnloadTrackedOverlay(int overlayId);
extern void func_02029fac(int arg, int handle);
extern void func_ov021_020a894c(void);
extern void func_ov001_0206c9dc(void);
extern void func_ov021_020a7ccc(void);
extern void func_ov021_020a9588(void);
extern void func_02050a58(void);
extern void func_ov001_0206a918(void *buffer);
extern void ResetGaugeDisplay(void);

void DestroyPartyState(void) {
    PartyState *party = data_ov001_020a04bc;
    int i;

    for (i = 0; i < party->count; i++) {
        PartyEntry *entry = &party->entries[i];
        PartyActor *actor = entry->actor;
        if (actor != NULL) {
            if (actor->destroy != NULL) {
                actor->destroy(actor);
            }
            NNSi_FndFreeFromDefaultHeap(actor);
        }
        if (entry->overlayId != -1) {
            UnloadTrackedOverlay(entry->overlayId);
        }
        entry->actor = NULL;
        entry->overlayId = -1;
        entry->flags = 0;
    }
    party->count = 0;
    if (party->handles[0] != -1) {
        func_02029fac(0, party->handles[0]);
        party->handles[0] = -1;
    }
    if (party->handles[1] != -1) {
        func_02029fac(0, party->handles[1]);
        party->handles[1] = -1;
    }
    if (party->handles[2] != -1) {
        func_02029fac(0, party->handles[2]);
        party->handles[2] = -1;
    }
    func_ov021_020a894c();
    func_ov001_0206c9dc();
    func_ov021_020a7ccc();
    func_ov021_020a9588();
    func_02050a58();
    if (party->buffers != NULL) {
        for (i = 0; i < 7; i++) {
            func_ov001_0206a918(party->buffers + i * 0x30);
        }
        NNSi_FndFreeFromDefaultHeap(party->buffers);
        party->buffers = NULL;
    }
    if (party->gauge != NULL) {
        ResetGaugeDisplay();
        party->gauge = NULL;
    }
}
