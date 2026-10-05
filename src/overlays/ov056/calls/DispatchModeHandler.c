#include "nitro/types.h"

typedef struct ModeObject ModeObject;
typedef void (*ModeHandler)(ModeObject *object, int arg1, int arg2);

struct ModeObject {
    u8 pad_00[4];
    int mode;
};

typedef struct ModeHandlerTable {
    ModeHandler handlers[20];
} ModeHandlerTable;

extern const ModeHandlerTable data_ov056_020d8080;

void DispatchModeHandler(ModeObject *object, int arg1, int arg2)
{
    ModeHandlerTable table = data_ov056_020d8080;
    table.handlers[object->mode](object, arg1, arg2);
}
