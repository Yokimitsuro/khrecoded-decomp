#include "nitro/types.h"

typedef struct TouchState {
    u8 pad_00[4];
    s16 x;
    s16 y;
    u16 state;
} TouchState;

typedef struct SoundPair {
    s16 seqArc;
    s16 index;
} SoundPair;

typedef struct YesNoDialog {
    u8 pad_0000[0x9c38];
    BOOL active : 1;
    BOOL selectedYes : 1;
    BOOL pressed : 1;
    u8 pad_9c3c[0x9c54 - 0x9c3c];
    void (*onResult)(void *arg, BOOL yes);
    void *resultArg;
    SoundPair sounds[2];
} YesNoDialog;

extern u16 data_02060500;

extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern TouchState *func_ov039_020bca20(void);
extern void GetDialogPixelBounds(YesNoDialog *dialog, int *bottom, int *left, int *right);
extern void BeginPickerFadeOut(YesNoDialog *dialog);

void UpdateYesNoDialogInput(YesNoDialog *dialog)
{
    int result = 0;
    int soundIndex = 1;
    TouchState *touch;
    BOOL released;
    int touchState;
    int bottom;
    int left;
    int right;
    int distance;
    SoundPair *sound;

    if (data_02060500 & 0x30) {
        dialog->selectedYes ^= 1;
        PlaySoundEffect(1, 0);
    } else if (data_02060500 & 1) {
        result = dialog->selectedYes ? 1 : 2;
        soundIndex = 0;
    } else if (data_02060500 & 0xa) {
        result = 2;
    } else {
        touch = func_ov039_020bca20();
        touchState = touch->state & 3;
        if (touchState != 0) {
            released = TRUE;
            GetDialogPixelBounds(dialog, &bottom, &left, &right);
            distance = touch->y - bottom;
            if (distance < 0) {
                distance = -distance;
            }
            if (distance <= 8) {
                distance = touch->x - left;
                if (distance < 0) {
                    distance = -distance;
                }
                if (distance <= 0x2d) {
                    released = FALSE;
                    if (touchState == 1) {
                        dialog->selectedYes = 1;
                        dialog->pressed = 1;
                    } else if (touchState == 2 && dialog->selectedYes) {
                        result = 1;
                        soundIndex = 0;
                    }
                } else {
                    distance = touch->x - right;
                    if (distance < 0) {
                        distance = -distance;
                    }
                    if (distance <= 0x2d) {
                        released = FALSE;
                        if (touchState == 1) {
                            dialog->selectedYes = 0;
                            dialog->pressed = 1;
                        } else if (touchState == 2 && !dialog->selectedYes) {
                            result = 2;
                        }
                    }
                }
            }
            if (released) {
                dialog->pressed = 0;
            }
        }
    }
    if (result != 0) {
        sound = &dialog->sounds[soundIndex];
        dialog->onResult(dialog->resultArg, result == 1);
        if (sound->seqArc >= 0 && sound->index >= 0) {
            PlaySoundEffect(sound->seqArc, sound->index);
        }
        BeginPickerFadeOut(dialog);
    }
}
