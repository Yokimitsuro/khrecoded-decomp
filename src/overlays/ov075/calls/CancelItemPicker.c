#include "nitro/types.h"

typedef struct ItemPicker ItemPicker;

extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern void func_ov075_020cde6c(ItemPicker *picker, BOOL closing);

s32 CancelItemPicker(ItemPicker *picker)
{
    PlaySoundEffect(1, 3);
    func_ov075_020cde6c(picker, TRUE);
    return 3;
}
