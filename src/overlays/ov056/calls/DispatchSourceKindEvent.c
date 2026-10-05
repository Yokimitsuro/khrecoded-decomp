#include "nitro/types.h"

typedef struct EffectSource EffectSource;
typedef void (*SourceEventHandler)(EffectSource *source, int arg1, int arg2);

struct EffectSource {
    u8 pad_00[0x3d];
    s8 kind;
};

typedef struct SourceEventTable {
    SourceEventHandler handlers[20];
} SourceEventTable;

extern const SourceEventTable data_ov056_020d80d0;

void DispatchSourceKindEvent(EffectSource *source, int arg1, int arg2)
{
    SourceEventTable table = data_ov056_020d80d0;
    table.handlers[source->kind](source, arg1, arg2);
}
