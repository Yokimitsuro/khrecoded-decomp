#include "nitro/types.h"

typedef struct ResultsWork {
    u8 pad_00[0x5c];
    u8 fadeTarget[0x649c];
    int fadeReady;
    int fadeActive;
    u8 pad_6500[0x694];
    u16 fadeParam;
    u8 pad_6b96[0x1a];
    int fadeMode;
    int syncSecondary;
    int brightness;
} ResultsWork;

extern ResultsWork *data_ov034_020c0fa0[2];
#define resultsWork (data_ov034_020c0fa0[1])
extern void UpdateWidgetRootAndFireAlarm(void *target, u16 param);
extern void SetBrightnessAndSyncMain(int brightness);
extern void SetSecondaryBrightness(int brightness);

void UpdateResultsFade(void)
{
    int mode;

    if (resultsWork->fadeActive == 0 || resultsWork->fadeReady == 0) {
        goto done;
    }
    UpdateWidgetRootAndFireAlarm(resultsWork->fadeTarget, resultsWork->fadeParam);
    mode = resultsWork->fadeMode;
    if (mode == 1 && resultsWork->brightness != 0) {
        if (resultsWork->brightness < 0) {
            resultsWork->brightness += 3;
            if (resultsWork->brightness > 0) {
                resultsWork->brightness = 0;
            }
        } else {
            resultsWork->brightness -= 1;
            if (resultsWork->brightness < 0) {
                resultsWork->brightness = 0;
            }
        }
        SetBrightnessAndSyncMain(resultsWork->brightness);
        if (resultsWork->syncSecondary != 0) {
            SetSecondaryBrightness(resultsWork->brightness);
        }
    } else if (mode == 0 && resultsWork->brightness > -16) {
        resultsWork->brightness -= 6;
        if (resultsWork->brightness < -16) {
            resultsWork->brightness = -16;
        }
        SetBrightnessAndSyncMain(resultsWork->brightness);
        if (resultsWork->syncSecondary != 0) {
            SetSecondaryBrightness(resultsWork->brightness);
        }
    } else if (mode == 2 && resultsWork->brightness < 16) {
        resultsWork->brightness += 6;
        if (resultsWork->brightness > 16) {
            resultsWork->brightness = 16;
        }
        SetBrightnessAndSyncMain(resultsWork->brightness);
        if (resultsWork->syncSecondary != 0) {
            SetSecondaryBrightness(resultsWork->brightness);
        }
    }
done:
    resultsWork->fadeActive = 0;
}
