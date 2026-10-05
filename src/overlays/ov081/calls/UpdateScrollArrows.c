#include "nitro/types.h"

typedef struct {
    u8 bytes[0x20];
} FadeRecord;

typedef struct Ov081State {
    u8 pad_00[0x63c8];
    BOOL arrowsShown;
    FadeRecord arrowFade;
} Ov081State;

typedef struct EntryList EntryList;

extern void *func_ov039_020bc1dc(void);
extern void *FindWidgetById(void *root, int id);
extern EntryList *func_ov081_020c544c(void);
extern void CountUnlockedListEntries(Ov081State *state, EntryList *list, int *total, int *before);
extern void SetEntrySlotsVisible(void *panel, void *element, BOOL visible);
extern void func_02052528(FadeRecord *record, int value0, int value1, int value2, int value3);
extern void func_02052570(FadeRecord *record);

void UpdateScrollArrows(Ov081State *state)
{
    void *panel = func_ov039_020bc1dc();
    void *leftArrow = FindWidgetById(panel, 1);
    void *rightArrow = FindWidgetById(panel, 2);
    int total;
    int before;

    CountUnlockedListEntries(state, func_ov081_020c544c(), &total, &before);
    if (total >= 2) {
        if (state->arrowsShown == FALSE) {
            state->arrowsShown = TRUE;
            SetEntrySlotsVisible(panel, leftArrow, TRUE);
            SetEntrySlotsVisible(panel, rightArrow, TRUE);
            func_02052528(&state->arrowFade, 0, 0, 0, 500);
            func_02052570(&state->arrowFade);
        }
    } else if (state->arrowsShown != FALSE) {
        state->arrowsShown = FALSE;
        SetEntrySlotsVisible(panel, leftArrow, FALSE);
        SetEntrySlotsVisible(panel, rightArrow, FALSE);
    }
}
