#include "nitro/types.h"

typedef struct Ov081State {
    u8 pad_00[0x20];
    u8 label[0x63ac];
    u8 tween[0x18];
    u32 flag0 : 1;
    u32 flag1 : 1;
    u32 tweenActive : 1;
} Ov081State;

extern void *func_ov081_020c544c(Ov081State *state);
extern void CountUnlockedListEntries(Ov081State *state, void *list, int *total, int *before);
extern int SampleTweenValue(void *tween, int *out);
extern void *func_ov039_020bc1dc(void);
extern void func_02052528(void *tween, int a, int b, int c, int duration);
extern void func_02052570(void *tween);
extern void *FindWidgetById(void *screen, int id);
extern BOOL GetField84Bit1(void *screen, void *widget);
extern void SetEntrySlotsVisible(void *screen, void *widget, BOOL visible);
extern char *func_ov081_020c5c04(int id);
extern void SPrintfUnbounded(char *dst, const char *fmt);
extern void func_ov081_020c5550(void *label, int a, const char *text, int b, int x, int y, int c, int d);
extern const char data_ov081_020c5d7c[];

void DrawListPageIndicator(Ov081State *state)
{
    int total;
    int before;
    int tweenValue;
    char text[24];
    void *screen;
    void *widget;

    CountUnlockedListEntries(state, func_ov081_020c544c(state), &total, &before);
    if (total >= 2) {
        SampleTweenValue(state->tween, &tweenValue);
        if (state->tweenActive) {
            screen = func_ov039_020bc1dc();
            func_02052528(state->tween, 0, 0, 0, 500);
            func_02052570(state->tween);
            widget = FindWidgetById(screen, 1);
            SetEntrySlotsVisible(screen, widget, !GetField84Bit1(screen, widget));
            widget = FindWidgetById(screen, 2);
            SetEntrySlotsVisible(screen, widget, !GetField84Bit1(screen, widget));
        }
        func_ov081_020c5550(state->label, 2, func_ov081_020c5c04(0), 1, 0x16, 0xc, 2, 0x20);
        return;
    }
    SPrintfUnbounded(text, data_ov081_020c5d7c);
    func_ov081_020c5550(state->label, 2, text, 1, 0x16, 0xc, 2, 0x20);
}
