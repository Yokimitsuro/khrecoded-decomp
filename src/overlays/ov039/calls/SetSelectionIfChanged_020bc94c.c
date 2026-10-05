extern int data_ov039_020bea20;
extern void FreeSlotPair(int base, int kind);
extern void func_ov039_020bb774(int base, int kind, int id);

void SetSelectionIfChanged_020bc94c(int id)
{
    int base = data_ov039_020bea20;

    if (id == *(int *)(base + 0xc994)) {
        return;
    }
    FreeSlotPair(base, 2);
    func_ov039_020bb774(base, 2, id);
    *(int *)(base + 0xc994) = id;
}
