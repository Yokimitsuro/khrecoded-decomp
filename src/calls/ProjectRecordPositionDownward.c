#include "nitro/types.h"

extern int ProjectPositionDownward(void *cont, int p3, void *out);
extern void *gActorRegistry;

int ProjectRecordPositionDownward(int p3, void *out) {
    return ProjectPositionDownward(gActorRegistry, p3, out);
}
