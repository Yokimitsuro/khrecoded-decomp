#include "nitro/types.h"

typedef struct FieldManager {
    u8 pad_000[0x490];
    char valueText[0x20];
    u8 pad_4B0[0x684];
    int choiceValues[1];
} FieldManager;

typedef struct FieldManagerHandle {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04c4;
extern const char data_ov001_0209ede4[];
extern void ClearChoiceHighlight(FieldManager *manager);
extern int OS_SNPrintf_0202e094(char *buffer, u32 size, const char *format, ...);

void FormatChoiceValueText(int index)
{
    FieldManager *manager = data_ov001_020a04c4.manager;

    ClearChoiceHighlight(manager);
    OS_SNPrintf_0202e094(manager->valueText, 0x20, data_ov001_0209ede4, manager->choiceValues[index]);
}
