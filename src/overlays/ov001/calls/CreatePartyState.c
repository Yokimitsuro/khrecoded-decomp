#include "nitro/types.h"

typedef struct PartyEntry {
    int id;
    void *actor;
    u8 pad_08[0x1c];
    u16 flags;
    u8 pad_26[2];
} PartyEntry;

typedef struct PartyState {
    int selected;
    PartyEntry entries[3];
    int count;
    int leaderId;
    int targetId;
    int focusId;
    int moveMode;
    int moveTimer;
    u8 pad_094[8];
    int moveScale;
    u8 pad_0A0[0x3c];
    u8 tracker[0x14];
    u8 isBusy;
    u8 pad_0F1[3];
    int busyTimer;
    u8 pad_0F8[4];
    int idleTimer;
} PartyState;

extern PartyState *data_ov001_020a04bc;
extern PartyState *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov001_0206cdec(void *tracker, int extended);
extern void OpenFieldMessageContainers(void);
extern void *UpdatePartyState(void);

void *CreatePartyState(void)
{
    PartyState *party = NNSi_FndGetCurrentRootHeap();
    int i;

    data_ov001_020a04bc = party;
    for (i = 0; i < 3; i++) {
        PartyEntry *entry = &party->entries[i];

        entry->actor = NULL;
        entry->id = -1;
        entry->flags = 0;
    }
    party->count = 0;
    party->leaderId = -1;
    party->targetId = -1;
    party->focusId = -1;
    party->moveMode = 1;
    party->moveTimer = 0;
    party->moveScale = 0x1000;
    party->selected = -1;
    party->idleTimer = 0;
    party->isBusy = 0;
    party->busyTimer = 0;
    func_ov001_0206cdec(party->tracker, 1);
    OpenFieldMessageContainers();
    return UpdatePartyState;
}
