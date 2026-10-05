#include "nitro/types.h"

typedef struct CommandOwner CommandOwner;
typedef void (*CommandHandler)(CommandOwner *owner, void *arg, s16 *command, void *extra);

typedef struct {
    CommandHandler handler;
    int mode;
} CommandEntry;

typedef struct {
    CommandEntry entries[12];
} CommandTable;

struct CommandOwner {
    u8 pad_00[0x10];
    int mode;
};

extern const CommandTable data_ov021_020b502c;
extern void func_02029f8c(int unused, int mode);

void DispatchCommandHandler(CommandOwner *owner, void *arg, s16 *command, void *extra)
{
    CommandTable table = data_ov021_020b502c;
    int index = -1;

    switch (*command) {
    case 0xbe:
        index = 0;
        break;
    case 0xbf:
        index = 1;
        break;
    case 0xc0:
        index = 2;
        break;
    case 0xc1:
        index = 3;
        break;
    case 0xc2:
        index = 4;
        break;
    case 0xc3:
        index = 5;
        break;
    case 0xc4:
        index = 6;
        break;
    case 0xc5:
        index = 7;
        break;
    case 0xc6:
        index = 8;
        break;
    case 0xc7:
    case 0x10f:
        index = 9;
        break;
    case 0xc8:
    case 0x110:
        index = 10;
        break;
    case 0xc9:
    case 0x111:
        index = 11;
        break;
    }
    owner->mode = table.entries[index].mode;
    func_02029f8c(0, table.entries[index].mode);
    table.entries[index].handler(owner, arg, command, extra);
}
