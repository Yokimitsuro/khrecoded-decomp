#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct TouchSample {
    u16 x;
    u16 y;
    u16 touching;
    u16 invalid;
} TouchSample;

typedef struct MapMenuState {
    u8 pad_00[0x10];
    void *screenData;
    u8 pad_14[0x10];
    BOOL screenPending;
    BOOL screenLoaded;
    BOOL dirty;
    u8 pad_30[0x4];
    BOOL cursorReset;
    BOOL menuShown;
    BOOL routeOpen;
    u8 pad_40[0x18];
    u8 renderer[0x6434];
    s32 markerSlot;
    u8 pad_6490[0x10];
    s32 menuSlot;
    u8 pad_64A4[0x1b08];
    TouchSample lastTouch;
    u8 pad_7FB4[0x8];
    u16 screenWidth;
    u16 screenHeight;
} MapMenuState;

extern MapMenuState *data_ov023_020b6f84;

extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern s32 func_ov001_0206dc38(void);
extern VecFx32 *func_ov001_0206dc4c(int index);
extern void ScrollMapToPosition(MapMenuState *state, VecFx32 *pos);
extern u16 GetBiasAdjustedField(int index);
extern void SetEntryRotation(void *renderer, int slot, int rotation);
extern BOOL IsFieldFlag13OrSessionFlagSet(void);
extern void PlaceMapStoryIcons(MapMenuState *state);
extern void func_ov023_020b65cc(MapMenuState *state);
extern void ResetMapMenuCursor(MapMenuState *state);
extern BOOL CanOpenFieldMenu(void);
extern BOOL func_ov001_0207b61c(void);
extern void IndexedRecords_SetFlag2(void *renderer, int slot, int value);
extern void *func_ov027_020b9f9c(TouchSample *out);
extern void func_ov001_0207b6dc(void);
extern void func_ov001_0207b348(int mode);
extern void PlaySoundEffect(int channel, int sound);
extern void func_ov001_0207b6ec(void);
extern void MI_CpuCopy8(const void *src, void *dest, u32 size);

void *UpdateMapMenuState(void)
{
    MapMenuState *state = data_ov023_020b6f84;
    TouchSample touch;

    if (state->screenLoaded && state->screenPending) {
        NNSi_FndFreeFromDefaultHeap(state->screenData);
        state->screenData = NULL;
        state->screenPending = FALSE;
        state->screenLoaded = FALSE;
    }
    if (state->screenWidth != 0 && state->screenHeight != 0) {
        if (func_ov001_0206dc38() > 0) {
            ScrollMapToPosition(state, func_ov001_0206dc4c(0));
            SetEntryRotation(state->renderer, state->markerSlot, GetBiasAdjustedField(0));
        }
        if (IsFieldFlag13OrSessionFlagSet()) {
            PlaceMapStoryIcons(state);
        }
        func_ov023_020b65cc(state);
    }
    if (state->cursorReset) {
        ResetMapMenuCursor(state);
    }
    if (state->routeOpen) {
        if (!state->menuShown && CanOpenFieldMenu() && func_ov001_0207b61c()) {
            IndexedRecords_SetFlag2(state->renderer, state->menuSlot, 1);
            state->menuShown = TRUE;
        } else if ((state->menuShown && !CanOpenFieldMenu()) || !func_ov001_0207b61c()) {
            IndexedRecords_SetFlag2(state->renderer, state->menuSlot, 0);
            state->menuShown = FALSE;
        }
    }
    func_ov027_020b9f9c(&touch);
    if (state->menuShown) {
        if (touch.touching == 1) {
            if (state->lastTouch.touching == 0 && touch.invalid == 0 && touch.x >= 0xc0 && touch.x <= 0xff
                && touch.y >= 0x86 && touch.y <= 0xa6) {
                func_ov001_0207b6dc();
                func_ov001_0207b348(2);
                PlaySoundEffect(0, 0x3b);
            }
        } else {
            func_ov001_0207b6ec();
        }
    }
    MI_CpuCopy8(&touch, &state->lastTouch, sizeof(TouchSample));
    state->dirty = TRUE;
    return NULL;
}
