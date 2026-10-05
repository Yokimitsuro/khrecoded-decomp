#include "nitro/types.h"

typedef struct PanelEvent {
    u8 kind;
    u8 value;
    u16 flags;
} PanelEvent;

extern char data_ov002_0206c420[];
extern void *func_0202a45c(void *descriptor, void *userData);

void PostPanelEventOff(u8 value)
{
    PanelEvent event;
    event.value = value;
    event.kind = 0;
    event.flags = 0x3000;
    func_0202a45c(data_ov002_0206c420, &event);
}
