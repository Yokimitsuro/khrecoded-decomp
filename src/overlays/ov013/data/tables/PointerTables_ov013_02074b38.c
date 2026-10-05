#include "nitro/types.h"

extern void func_ov013_0207423c(void);
extern void LoadPanelPaletteBase(void); /* LoadPanelPaletteBase */
extern void ScrollPanelSlotsUp(void); /* ScrollPanelSlotsUp */
extern void func_ov013_02074348(void);
extern void func_ov013_0207434c(void);
extern void ScrollPanelSlotsDown(void); /* ScrollPanelSlotsDown */
extern void func_ov013_0207441c(void);
extern void func_ov013_02074238(void);

void (*gPanelScrollHandlers[7])(void) = {
    func_ov013_0207423c,
    LoadPanelPaletteBase, /* LoadPanelPaletteBase */
    ScrollPanelSlotsUp, /* ScrollPanelSlotsUp */
    func_ov013_02074348,
    func_ov013_0207434c,
    ScrollPanelSlotsDown, /* ScrollPanelSlotsDown */
    func_ov013_0207441c,
};

void (*gPanelScrollInitCallback[1])(void) = {
    func_ov013_02074238,
};
