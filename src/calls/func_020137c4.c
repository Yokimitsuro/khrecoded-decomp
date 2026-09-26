typedef struct {
    char bytes[0x18];
} RosterEntry;

typedef struct {
    char pad0000[8];
    RosterEntry *slots[5];
} PartyState;

extern RosterEntry data_02055c78[];
extern PartyState data_02055c5c;

void func_020137c4(int a, int b, int c, int d, int e) {
    data_02055c5c.slots[0] = &data_02055c78[a];
    data_02055c5c.slots[1] = &data_02055c78[b];
    data_02055c5c.slots[2] = &data_02055c78[c];
    data_02055c5c.slots[3] = &data_02055c78[d];
    data_02055c5c.slots[4] = &data_02055c78[e];
}
