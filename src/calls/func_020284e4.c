#include "nitro/types.h"

extern u32 func_ov001_02063838();
extern u32 func_ov001_02088844();
extern u32 func_ov036_020bc600();

void func_020284e4(void) {
  int active;

  active = func_ov001_02063838();
  if (active != 0) {
    func_ov001_02088844();
    return;
  }
  func_ov036_020bc600();
}
