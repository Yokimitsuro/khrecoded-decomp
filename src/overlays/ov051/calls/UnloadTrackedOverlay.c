extern void func_02029fac(int processor, int overlayId);
extern int data_ov051_020c7460[3];
void UnloadTrackedOverlay(int overlayId)
{
    int slot;
    func_02029fac(0, overlayId);
    for (slot = 0; slot < 3; ++slot) {
        if (data_ov051_020c7460[slot] == overlayId) {
            data_ov051_020c7460[slot] = -1;
            return;
        }
    }
}
