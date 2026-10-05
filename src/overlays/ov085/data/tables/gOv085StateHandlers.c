#include "nitro/types.h"

extern void StepPickerForward(void);
extern void ConfirmItemMenuChoice(void);
extern void CancelPicker(void);
extern void SelectPrevTab(void);
extern void SelectNextTab(void);

void (*gOv085StateHandlers[9])(void) = {
    StepPickerForward,
    ConfirmItemMenuChoice,
    CancelPicker,
    NULL,
    NULL,
    SelectPrevTab,
    SelectNextTab,
    NULL,
    CancelPicker,
};
