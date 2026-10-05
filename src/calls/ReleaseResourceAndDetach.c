#include "nitro/types.h"

extern void func_0202eb08(void *tables);
extern void ReleaseResourceSlot(void);
extern void ReleaseSharedRecordSlot(void *resource);
extern void DetachObjectTreeNode(void *object);

void ReleaseResourceAndDetach(u8 *object) {
    func_0202eb08(object + 0xd8);
    if (*(void **)(object + 0x74) != NULL) {
        ReleaseResourceSlot();
        ReleaseSharedRecordSlot(*(void **)(object + 0x74));
    }
    *(void **)(object + 0x74) = NULL;
    DetachObjectTreeNode(object);
}
