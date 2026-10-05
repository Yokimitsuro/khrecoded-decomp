#include "nitro/types.h"

typedef struct {
    s32 count;
    s32 initial;
    u16 **strings;
    u32 unk_0c;
} ChoiceList;

typedef struct {
    u8 pad_00[0x38];
    u16 *text;
    u16 *cursor;
    u8 pad_40[0x54 - 0x40];
    ChoiceList choices;
} TextPrompt;

extern int Utf16Length(u16 *text);
extern u16 *Utf16CopyPadded(u16 *destination, u16 *source, int unitCount);
extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 size, int align);
extern void MI_CpuFill8(void *dst, u8 val, u32 size);

void SetTextAndChoices(TextPrompt *prompt, u16 *text, ChoiceList *source) {
    ChoiceList *choices = &prompt->choices;
    int length = Utf16Length(text);
    u16 *buffer = NNS_FndAllocFromDefaultExpHeapEx((length + 1) * 2, -4);
    int i;

    prompt->text = buffer;
    prompt->cursor = buffer;
    Utf16CopyPadded(buffer, text, length);
    prompt->text[length] = 0;
    i = 0;
    if (source != NULL) {
        choices->count = source->count;
        choices->initial = source->initial;
        choices->strings = NNS_FndAllocFromDefaultExpHeapEx(source->count * 4, -4);
        for (; i < choices->count; i++) {
            u16 *choice = source->strings[i];
            length = Utf16Length(choice);
            choices->strings[i] = NNS_FndAllocFromDefaultExpHeapEx((length + 1) * 2, -4);
            Utf16CopyPadded(choices->strings[i], choice, length);
            choices->strings[i][length] = 0;
        }
    } else {
        MI_CpuFill8(choices, 0, sizeof(ChoiceList));
    }
}
