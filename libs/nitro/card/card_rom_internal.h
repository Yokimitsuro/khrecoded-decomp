#ifndef CARD_ROM_INTERNAL_H
#define CARD_ROM_INTERNAL_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef volatile u16 vu16;
typedef volatile u32 vu32;

#define REG_MCCNT0 (*(vu16 *)0x040001a0)
#define REG_MCCNT1 (*(vu32 *)0x040001a4)
#define REG_MCCMD0 (*(vu32 *)0x040001a8)
#define REG_MCCMD1 (*(vu32 *)0x040001ac)
#define REG_MCD1 (*(vu32 *)0x04100010)
#define CARD_ROM_CTRL (*(vu32 *)0x02fffae0)
#define CARD_BOOT_ID (*(vu32 *)0x02fffc00)

#define CARD_COMMAND_PAGE 0x01000000UL
#define CARD_COMMAND_ID 0x07000000UL
#define CARD_COMMAND_MASK 0x07000000UL
#define CARD_RESET_HI 0x20000000UL
#define CARD_START 0x80000000UL
#define CARD_DATA_READY 0x00800000UL
#define CARD_LATENCY1_MASK 0x00001fffUL

#define CARDi_GetRomFlag(flag) \
    ((flag) | CARD_START | CARD_RESET_HI | \
     (CARD_ROM_CTRL & ~CARD_COMMAND_MASK))

#define MI_HToBE32(value) \
    ((((value) & 0xff000000UL) >> 24UL) | \
     (((value) & 0x00ff0000UL) >> 8UL) | \
     (((value) & 0x0000ff00UL) << 8UL) | \
     (((value) & 0x000000ffUL) << 24UL))

void CARDi_SetRomOp(u32 command, u32 offset);
void CARDi_RefreshRomCore(void);
u32 CARDi_ReadRomStatusCore(void);

#endif
