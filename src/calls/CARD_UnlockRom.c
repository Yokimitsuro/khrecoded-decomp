extern void func_02002344(int id);
extern void CARDi_UnlockResource(int id, int resource);

void CARD_UnlockRom(int id) {
    func_02002344(id);
    CARDi_UnlockResource(id, 1);
}
