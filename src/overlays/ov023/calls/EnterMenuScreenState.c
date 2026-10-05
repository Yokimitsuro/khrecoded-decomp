extern unsigned int data_ov023_020b6f80;
extern unsigned int func_ov001_0207b1a8();
extern unsigned int func_ov023_020b5944();
extern unsigned int func_ov023_020b5a4c(void);
extern unsigned int DrawCacheHeaderText();

unsigned int EnterMenuScreenState(void)

{
  unsigned int nextState;
  
  nextState = 0;
  if (*(int *)(data_ov023_020b6f80 + 4) != 0) {
    nextState = (unsigned int)func_ov023_020b5a4c;
    func_ov023_020b5944(data_ov023_020b6f80);
    func_ov001_0207b1a8();
    DrawCacheHeaderText();
  }
  return nextState;
}
