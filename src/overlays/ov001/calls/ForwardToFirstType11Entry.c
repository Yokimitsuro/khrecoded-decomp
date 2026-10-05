#include "nitro/types.h"

typedef struct {
    u8 pad[0x7d];
    u8 type;
} Entry;

extern int func_ov001_0207f040(void);
extern Entry *func_ov001_0207f050(int index);
extern int LaunchMatchingFieldObject(Entry *entry, int arg0, int arg1);

int ForwardToFirstType11Entry(int arg0, int arg1) {
    int i;
    int count = func_ov001_0207f040();
    for (i = 0; i < count; i++) {
        Entry *entry = func_ov001_0207f050(i);
        if (entry->type == 11) {
            return LaunchMatchingFieldObject(entry, arg0, arg1);
        }
    }
    return 0;
}
