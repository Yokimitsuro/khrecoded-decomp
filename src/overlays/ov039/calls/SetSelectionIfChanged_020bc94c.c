extern int data_ov039_020bea20;
extern void FreeSlotPair(int base, int kind);
extern void LoadSlotImagePair(int base, int kind, int id);

void SetSelectionIfChanged_020bc94c(int id)
{
    int base = data_ov039_020bea20;

    if (id == *(int *)(base + 0xc994)) {
        return;
    }
    FreeSlotPair(base, 2);
    LoadSlotImagePair(base, 2, id);
    *(int *)(base + 0xc994) = id;
}
