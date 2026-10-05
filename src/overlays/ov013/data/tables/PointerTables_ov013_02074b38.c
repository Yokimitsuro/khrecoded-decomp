#include "nitro/types.h"

extern void func_ov013_0207423c(void);
extern void LoadPanelPaletteBase(void); /* LoadPanelPaletteBase */
extern void func_ov013_020742a4(void); /* ScrollPanelSlotsUp */
extern void func_ov013_02074348(void);
extern void func_ov013_0207434c(void);
extern void func_ov013_0207436c(void); /* ScrollPanelSlotsDown */
extern void func_ov013_0207441c(void);
extern void func_ov013_02074238(void);

void (*gPanelScrollHandlers[7])(void) = {
    func_ov013_0207423c,
    LoadPanelPaletteBase, /* LoadPanelPaletteBase */
    func_ov013_020742a4, /* ScrollPanelSlotsUp */
    func_ov013_02074348,
    func_ov013_0207434c,
    func_ov013_0207436c, /* ScrollPanelSlotsDown */
    func_ov013_0207441c,
};

void (*gPanelScrollInitCallback[1])(void) = {
    func_ov013_02074238,
};
