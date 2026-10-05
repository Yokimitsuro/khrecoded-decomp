#include "nitro/types.h"

extern int data_ov039_020bea20;
extern void func_ov027_020b85c8(unsigned char *flags, int value);
extern void func_ov027_020b85e4(int button);
extern void SetWidgetRootDpadEnabled(int root, BOOL enabled);
extern void SetWidgetRootTouchEnabled(int root, BOOL enabled);

void SetMenuButtonsEnabled(BOOL enable)
{
    int base = data_ov039_020bea20;
    BOOL first = enable && *(int *)(base + 0xca18) != 0;
    BOOL second = enable && *(int *)(base + 0xca1c) != 0;

    func_ov027_020b85c8((unsigned char *)(base + 0xc8f8), first);
    func_ov027_020b85c8((unsigned char *)(base + 0xc944), second);
    func_ov027_020b85e4(base + 0xc8f8);
    func_ov027_020b85e4(base + 0xc944);
    SetWidgetRootDpadEnabled(base + 0x647c, second);
    SetWidgetRootTouchEnabled(base + 0x647c, second);
}
