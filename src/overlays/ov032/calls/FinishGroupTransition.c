extern int data_ov032_020c0080[];
#define activeGroup_020c0064 data_ov032_020c0080[1]
extern unsigned int data_ov001_020a0480;
extern unsigned int IsScreenModeIdle();
extern unsigned int Panel_CaptureBrightness();

unsigned int FinishGroupTransition(void)

{
  int group;
  int ready;
  
  group = activeGroup_020c0064;
  ready = IsScreenModeIdle();
  if (ready == 0) {
    return 0xffffffff;
  }
  *(unsigned short *)(group + 6) = *(unsigned short *)(group + 6) & 0xffdf;
  if ((*(unsigned short *)(group + 6) & 0x4000) == 0) {
    if (*(char *)(group + 8) != '\x03') {
      *(unsigned int *)(data_ov001_020a0480 + 0x214) = *(unsigned int *)(data_ov001_020a0480 + 0x214) & 0xfffbffff
      ;
      Panel_CaptureBrightness();
    }
    *(signed char *)(group + 8) = -1;
  }
  return 7;
}
