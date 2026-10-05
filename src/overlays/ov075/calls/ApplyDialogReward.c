#include "nitro/types.h"

extern u32 AddSessionCounter();
extern u32 AddToSelectionCounters();
extern u32 ApplyLevelRankParam();
extern u32 func_ov075_020ce818();
extern u32 func_ov075_020ce820();

void ApplyDialogReward(u32 reward)

{
  switch(reward) {
  case 0xb7:
    AddToSelectionCounters(0x1e);
    AddSessionCounter(5,1);
    func_ov075_020ce820(0xb2,0);
    return;
  case 0xb8:
    AddToSelectionCounters(0x32);
    AddSessionCounter(5,1);
    func_ov075_020ce820(0xb3,0);
    return;
  case 0xbb:
    func_ov075_020ce818();
    AddSessionCounter(5,1);
    func_ov075_020ce820(0xb6,0);
    return;
  case 0xb9:
    ApplyLevelRankParam(1);
    func_ov075_020ce820(0xb4,0);
    return;
  case 0xba:
    ApplyLevelRankParam(2);
    func_ov075_020ce820(0xb5,0);
    return;
  case 0xbc:
    AddToSelectionCounters(1000);
    func_ov075_020ce818();
    AddSessionCounter(5,1);
    func_ov075_020ce820(0xb7,0);
    return;
  case 0xbd:
    ApplyLevelRankParam(4);
    AddToSelectionCounters(1000);
    func_ov075_020ce818();
    AddSessionCounter(5,1);
    AddSessionCounter(0x12,1);
    func_ov075_020ce820(0xb8,0);
  }
  return;
}
