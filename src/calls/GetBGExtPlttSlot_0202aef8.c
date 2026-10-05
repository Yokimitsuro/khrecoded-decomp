#include "nitro/types.h"
#include "nitro/os_types.h"

typedef enum NNSG2dBGSelect {
    NNS_G2D_BGSELECT_MAIN0,
    NNS_G2D_BGSELECT_MAIN1,
    NNS_G2D_BGSELECT_MAIN2,
    NNS_G2D_BGSELECT_MAIN3,
    NNS_G2D_BGSELECT_SUB0,
    NNS_G2D_BGSELECT_SUB1,
    NNS_G2D_BGSELECT_SUB2,
    NNS_G2D_BGSELECT_SUB3,
    NNS_G2D_BGSELECT_NUM
} NNSG2dBGSelect;

typedef enum NNSG2dBGExtPlttSlot {
    NNS_G2D_BGEXTPLTTSLOT_MAIN0,
    NNS_G2D_BGEXTPLTTSLOT_MAIN1,
    NNS_G2D_BGEXTPLTTSLOT_MAIN2,
    NNS_G2D_BGEXTPLTTSLOT_MAIN3,
    NNS_G2D_BGEXTPLTTSLOT_SUB0,
    NNS_G2D_BGEXTPLTTSLOT_SUB1,
    NNS_G2D_BGEXTPLTTSLOT_SUB2,
    NNS_G2D_BGEXTPLTTSLOT_SUB3
} NNSG2dBGExtPlttSlot;

typedef void *OSMessage;

#define HW_MAIN_MEM 0x02000000

#define offsetof(type, member) ((u32)&(((type *)0)->member))

#define HW_IOREG 0x04000000
#define HW_REG_BASE HW_IOREG
#define REG_BG0CNT_OFFSET 0x008
#define REG_BG1CNT_OFFSET 0x00a
#define REG_G2_BG0CNT_BGPLTTSLOT_MASK 0x2000
#define REG_DB_BG0CNT_OFFSET 0x1008
#define REG_DB_BG1CNT_OFFSET 0x100a

extern const u16 data_02055580[8];

NNSG2dBGExtPlttSlot GetBGExtPlttSlot_0202aef8 (NNSG2dBGSelect bg)
{
    u32 addr;
    NNSG2dBGExtPlttSlot slot = (NNSG2dBGExtPlttSlot)bg;

    addr = data_02055580[bg];

    if (addr != 0) {
        addr += HW_REG_BASE;

        if ((*(u16 *)addr & REG_G2_BG0CNT_BGPLTTSLOT_MASK) != 0) {
            slot += 2;
        }
    }

    return slot;
}
