typedef struct RosterEntry {
    unsigned char data[0x18];
} RosterEntry;

typedef struct PartyState {
    unsigned char header[8];
    RosterEntry *activeSlots[5];
} PartyState;

extern RosterEntry gRosterEntries[];
extern PartyState gPartyState;

void Party_SetActiveSlots(int first, int second, int third, int fourth, int fifth)
{
    gPartyState.activeSlots[0] = &gRosterEntries[first];
    gPartyState.activeSlots[1] = &gRosterEntries[second];
    gPartyState.activeSlots[2] = &gRosterEntries[third];
    gPartyState.activeSlots[3] = &gRosterEntries[fourth];
    gPartyState.activeSlots[4] = &gRosterEntries[fifth];
}
