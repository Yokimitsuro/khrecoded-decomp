#include "nitro/types.h"

extern int ProjectPositionDownward(void *cont, int p3, void *out);
extern void *data_0206083c;

int ProjectRecordPositionDownward(int p3, void *out) {
    return ProjectPositionDownward(data_0206083c, p3, out);
}
