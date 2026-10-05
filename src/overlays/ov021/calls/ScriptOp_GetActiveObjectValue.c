extern int data_ov021_020b56c4[];
#define activeObject_020b56ac data_ov021_020b56c4[2]
extern unsigned int func_ov001_02091840();

unsigned int ScriptOp_GetActiveObjectValue(int context)

{
  unsigned int value;
  
  if (activeObject_020b56ac == 0) {
    return 0;
  }
  *(unsigned short *)(context + 0x2c) = 0x10;
  value = func_ov001_02091840(activeObject_020b56ac);
  *(unsigned int *)(context + 0x30) = value;
  return 0;
}
