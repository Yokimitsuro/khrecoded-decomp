#include "nitro/types.h"

extern void func_0202eb08(void *tables);
extern void func_0202ca2c(void);
extern void func_0202c8bc(void *resource);
extern void DetachObjectTreeNode(void *object);

void ReleaseResourceAndDetach(u8 *object) {
    func_0202eb08(object + 0xd8);
    if (*(void **)(object + 0x74) != NULL) {
        func_0202ca2c();
        func_0202c8bc(*(void **)(object + 0x74));
    }
    *(void **)(object + 0x74) = NULL;
    DetachObjectTreeNode(object);
}
