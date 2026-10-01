extern void func_02002344(int id);
extern void func_0200923c(int id, int resource);

void CARD_UnlockRom(int id) {
    func_02002344(id);
    func_0200923c(id, 1);
}
