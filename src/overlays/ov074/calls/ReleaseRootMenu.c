#include "nitro/types.h"

#define REG_BG0CNT (*(vu16 *)0x04000008)
#define REG_BG1CNT (*(vu16 *)0x0400000a)
#define REG_BG2CNT (*(vu16 *)0x0400000c)

typedef struct RenderObj {
    u32 flag;
    u8 pad_04[0x30];
    void *cbFunc;
    void *cbInitFunc;
} RenderObj;

typedef struct TextWindow {
    u8 data[0x34];
} TextWindow;

typedef struct RootMenu {
    u8 pad_00[8];
    BOOL isFullMenu;
    u8 pad_0c[8];
    int textureKeyA;
    int textureKeyB;
    u8 model[0x20];
    RenderObj renderObj;
    u8 pad_78[0x120 - 0x78];
    u8 weapon[0x230];
    u8 animA[0x24];
    u8 animB[0x24];
    u8 pad_398[0x438 - 0x398];
    TextWindow windows[4];
    u8 pad_508[0x5dc - 0x508];
    u8 strings[0xc];
} RootMenu;

extern void *func_ov039_020bc1dc(void);
extern int func_ov039_020bc1ac(void);
extern void func_ov027_020b833c(int context);
extern void DestroyAllContainerElements(void *container);
extern void ReleaseIfMarked(void *container);
extern void NNS_G3dRenderObjResetCallBack(RenderObj *renderObj);
extern void ReleaseModelSet(void *weapon);
extern void ReleaseResourceAndDetach(void *model);
extern void func_0202eb08(void *anim);
extern void ZeroHalfThenFree(int key);
extern void func_ov021_020a9588(void);
extern void G3X_SetHOffset(int value);
extern void NNS_GfdResetFrmTexVramState(void);
extern void NNS_GfdResetFrmPlttVramState(void);
extern void FreePointerIfSet(void *table);
extern void DestroyFndObjectList(TextWindow *window);

void ReleaseRootMenu(RootMenu *menu)
{
    void *container = func_ov039_020bc1dc();

    func_ov027_020b833c(func_ov039_020bc1ac());
    DestroyAllContainerElements(container);
    ReleaseIfMarked(container);
    if (menu->isFullMenu) {
        NNS_G3dRenderObjResetCallBack(&menu->renderObj);
        menu->renderObj.cbFunc = NULL;
        if (menu->renderObj.cbInitFunc == NULL) {
            menu->renderObj.flag &= ~1;
        }
        ReleaseModelSet(menu->weapon);
        ReleaseResourceAndDetach(menu->model);
        func_0202eb08(menu->animB);
        func_0202eb08(menu->animA);
        ZeroHalfThenFree(menu->textureKeyB);
        ZeroHalfThenFree(menu->textureKeyA);
        func_ov021_020a9588();
    }
    G3X_SetHOffset(0);
    REG_BG0CNT = REG_BG0CNT & ~3;
    REG_BG1CNT = (REG_BG1CNT & ~3) | 1;
    REG_BG2CNT = (REG_BG2CNT & 0x43) | 0x1e00;
    NNS_GfdResetFrmTexVramState();
    NNS_GfdResetFrmPlttVramState();
    FreePointerIfSet(menu->strings);
    DestroyFndObjectList(&menu->windows[3]);
    DestroyFndObjectList(&menu->windows[0]);
    DestroyFndObjectList(&menu->windows[1]);
    DestroyFndObjectList(&menu->windows[2]);
}
