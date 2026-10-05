#include "nitro/types.h"

typedef struct TextWindow {
    u8 pad_00[0x2c];
    u16 tileOffset;
    u16 width;
    u16 height;
    u8 pad_32;
    u8 bgLayer;
} TextWindow;

typedef struct Scene {
    u8 pad_000[0x1f8];
    s32 choiceMenuActive;
    TextWindow choiceWindow;
    void *choiceLines[4];
    s32 highlightDrawn;
    s32 highlightX;
    s32 highlightY;
} Scene;

extern void *func_ov001_0207123c(Scene *scene);
extern void func_ov027_020b9d74(void *widgets, int layer, int x, int y, int width, int height);
extern void func_ov027_020b9e20(void *widgets, int layer);

void ClearChoiceHighlight(Scene *scene)
{
    void *widgets = func_ov001_0207123c(scene);
    TextWindow *window = &scene->choiceWindow;

    if (scene->choiceMenuActive != 0 && scene->highlightDrawn != 0) {
        func_ov027_020b9d74(widgets, 0xb, scene->highlightX, scene->highlightY, window->width + 2, 7);
        func_ov027_020b9e20(widgets, 0xb);
        scene->highlightDrawn = 0;
    }
}
