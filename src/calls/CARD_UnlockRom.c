extern void OS_UnlockCard(int id);
extern void CARDi_UnlockResource(int id, int resource);

void CARD_UnlockRom(int id) {
    OS_UnlockCard(id);
    CARDi_UnlockResource(id, 1);
}
