#include "nitro/types.h"

extern u32 ResetMotionState();

void InitializeUnitParameters(int owner,u32 *parameters,int unit)

{
  u32 vectorY;
  u32 vectorZ;
  
  *(u32 *)(owner + 0x178) = *parameters;
  *(u32 *)(owner + 0x17c) = parameters[1];
  *(u32 *)(owner + 0x180) = parameters[0xc];
  *(u32 *)(owner + 0x184) = parameters[0xd];
  ResetMotionState(unit);
  *(u32 *)(unit + 0x30) = 1;
  *(short *)(unit + 0x58) = *(short *)(owner + 0x188);
  *(short *)(unit + 8) = (short)parameters[2];
  *(u32 *)(unit + 0x10) = parameters[3];
  *(u32 *)(unit + 0x18) = parameters[4];
  *(u32 *)(unit + 0x1c) = parameters[5];
  *(u32 *)(unit + 0x24) = parameters[6];
  *(u32 *)(unit + 0x14) = parameters[7];
  *(u32 *)(unit + 0x28) = parameters[8];
  *(u32 *)(unit + 0x2c) = parameters[9];
  *(u32 *)(unit + 0x34) = parameters[10];
  *(u32 *)(unit + 0x38) = parameters[0xb];
  *(u32 *)(unit + 0x20) = parameters[0xe];
  *(u32 *)(unit + 0xc) = parameters[0xf];
  *(u32 *)(unit + 0x54) = parameters[0x10];
  *(u32 *)(unit + 0x50) = parameters[0x11];
  vectorZ = parameters[0x14];
  vectorY = parameters[0x13];
  *(u32 *)(unit + 0x40) = parameters[0x12];
  *(u32 *)(unit + 0x44) = vectorY;
  *(u32 *)(unit + 0x48) = vectorZ;
  return;
}
