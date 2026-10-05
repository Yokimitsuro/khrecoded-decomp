#include "nitro/types.h"

typedef struct TouchState {
    u8 pad_00[0x4];
    s16 x;
    s16 y;
    u16 flags;
} TouchState;

typedef struct ChoiceSound {
    s16 id;
    s16 channel;
} ChoiceSound;

typedef void (*ChoiceCallback)(void *arg, BOOL yes);

typedef struct MessageWindow {
    u8 pad_0000[0x9c38];
    BOOL finished : 1;
    BOOL cursorYes : 1;
    BOOL pressed : 1;
    u8 pad_9c3c[0x9c54 - 0x9c3c];
    ChoiceCallback onChoice;
    void *choiceArg;
    ChoiceSound sounds[2];
} MessageWindow;

extern u16 data_02060500;
extern void PlaySoundEffect(int id, int channel);
extern TouchState *func_ov039_020bca20(void);
extern void func_ov077_020c7e5c(MessageWindow *window, int *outTop, int *outLeft, int *outRight);
extern void MessageWindow_BeginClosing_020c84bc(MessageWindow *window);

void HandleYesNoWindowInput(MessageWindow *window)
{
    int choice = 0;
    int soundIndex = 1;
    TouchState *touch;
    ChoiceSound *sound;
    int mode;
    BOOL release;
    int top;
    int left;
    int right;
    int dist;

    if (data_02060500 & 0x30) {
        window->cursorYes ^= 1;
        PlaySoundEffect(1, 0);
    } else if (data_02060500 & 1) {
        choice = window->cursorYes ? 1 : 2;
        soundIndex = 0;
    } else if (data_02060500 & 0xa) {
        choice = 2;
    } else {
        touch = func_ov039_020bca20();
        mode = touch->flags & 3;
        if (mode != 0) {
            release = TRUE;
            func_ov077_020c7e5c(window, &top, &left, &right);
            dist = touch->y - top;
            if (dist < 0) {
                dist = -dist;
            }
            if (dist <= 8) {
                dist = touch->x - left;
                if (dist < 0) {
                    dist = -dist;
                }
                if (dist <= 0x2d) {
                    release = FALSE;
                    if (mode == 1) {
                        window->cursorYes = 1;
                        window->pressed = 1;
                    } else if (mode == 2 && window->cursorYes) {
                        choice = 1;
                        soundIndex = 0;
                    }
                } else {
                    dist = touch->x - right;
                    if (dist < 0) {
                        dist = -dist;
                    }
                    if (dist <= 0x2d) {
                        release = FALSE;
                        if (mode == 1) {
                            window->cursorYes = 0;
                            window->pressed = 1;
                        } else if (mode == 2 && !window->cursorYes) {
                            choice = 2;
                        }
                    }
                }
            }
            if (release) {
                window->pressed = 0;
            }
        }
    }
    if (choice != 0) {
        sound = &window->sounds[soundIndex];
        window->onChoice(window->choiceArg, choice == 1);
        if (sound->id >= 0 && sound->channel >= 0) {
            PlaySoundEffect(sound->id, sound->channel);
        }
        MessageWindow_BeginClosing_020c84bc(window);
    }
}
