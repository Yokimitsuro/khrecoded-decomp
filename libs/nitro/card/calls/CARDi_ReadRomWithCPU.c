#include "libs/nitro/card/card_rom_internal.h"

extern void MI_CpuCopy8(const void *source, void *destination, u32 length);
CARDRomConfig sCardRomConfig = { 1, 1 };

u8 sCardRomCacheBuffer[CARD_ROM_PAGE_SIZE] __attribute__((aligned(32)));
#define cache_page sCardRomConfig.cachedPage
#define CARDi_cache_buf sCardRomCacheBuffer

#define MATH_ROUNDDOWN(x, base) ((x) & ~((base) - 1))
#define MATH_MIN(a, b) (((a) <= (b)) ? (a) : (b))

int CARDi_ReadRomWithCPU(void *userdata, void *buffer, u32 offset, u32 length) {
  int retval = (int)length;

  u32 cachedPage = cache_page;
  u8 *const cacheBuffer = CARDi_cache_buf;
  while (length > 0) {

    u8 *ptr = (u8 *)buffer;
    u32 n = CARD_ROM_PAGE_SIZE;
    u32 pos = MATH_ROUNDDOWN(offset, CARD_ROM_PAGE_SIZE);

    if (pos == cachedPage) {
      ptr = cacheBuffer;
    } else {

      if (((pos != offset) || (((u32)buffer & 3) != 0) || (length < n))) {
        cachedPage = pos;
        ptr = cacheBuffer;
      }

      CARDi_StartRomPageTransfer(pos);
      {
        u32 word = 0;
        for (;;) {

          u32 ctrl = REG_MCCNT1;
          if ((ctrl & CARD_DATA_READY) != 0) {

            u32 data = REG_MCD1;
            if (word < (CARD_ROM_PAGE_SIZE / sizeof(u32))) {
              ((u32 *)ptr)[word++] = data;
            }
          }

          if ((ctrl & CARD_START) == 0) {
            break;
          }
        }
      }
    }

    if (ptr == cacheBuffer) {
      u32 mod = offset - pos;
      n = MATH_MIN(length, CARD_ROM_PAGE_SIZE - mod);
      MI_CpuCopy8(cacheBuffer + mod, buffer, n);
    }
    buffer = (u8 *)buffer + n;
    offset += n;
    length -= n;
  }

  CARDi_CheckPulledOutCore(CARDi_ReadRomIDCore());

  cache_page = cachedPage;
  (void)userdata;
  return retval;
}
