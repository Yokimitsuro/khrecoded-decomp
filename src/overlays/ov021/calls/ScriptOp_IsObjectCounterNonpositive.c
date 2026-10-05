extern unsigned int func_ov021_020b0270();
extern unsigned int ResolveTaggedValueRef();

unsigned int ScriptOp_IsObjectCounterNonpositive(int context,int operands)

{
  int object;
  
  object = ResolveTaggedValueRef(context,operands + 8);
  object = func_ov021_020b0270(context,*(unsigned int *)(object + 4));
  if (object != 0) {
    *(unsigned short *)(context + 0x2c) = 1;
    *(unsigned int *)(context + 0x30) = (unsigned int)(*(int *)(object + 0x70) <= 0);
  }
  return 0;
}
