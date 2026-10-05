#include "nitro/types.h"

extern int data_ov013_02074ce0;
extern int FindWidgetById(int panel, int id);
extern void func_ov027_020b9640(int panel, int handle);

/* Refreshes linked panel objects 0, 2, and 3. */
void RefreshPanelSlotLinks(void) {
    int handle;

    handle = FindWidgetById(data_ov013_02074ce0 + 0x6818, 0);
    func_ov027_020b9640(data_ov013_02074ce0 + 0x6818, handle);
    handle = FindWidgetById(data_ov013_02074ce0 + 0x6818, 2);
    func_ov027_020b9640(data_ov013_02074ce0 + 0x6818, handle);
    handle = FindWidgetById(data_ov013_02074ce0 + 0x6818, 3);
    func_ov027_020b9640(data_ov013_02074ce0 + 0x6818, handle);
}
