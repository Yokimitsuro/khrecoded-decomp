extern unsigned int func_ov001_02063a24();
extern unsigned int func_ov001_02063a38();
extern unsigned int FlushMarkerPosition();
extern unsigned int ResolveTaggedValueRef();
extern unsigned int TaggedValueToFixed();

unsigned int ScriptOp_ApplyStageEventOutsideModeSeven(unsigned int context,int operands)

{
  int event;
  unsigned int firstValue;
  unsigned int secondValue;
  unsigned int thirdValue;
  int mode;
  
  event = ResolveTaggedValueRef(context,operands);
  firstValue = ResolveTaggedValueRef(context,operands + 8);
  secondValue = ResolveTaggedValueRef(context,operands + 0x10);
  thirdValue = ResolveTaggedValueRef(context,operands + 0x18);
  TaggedValueToFixed(firstValue);
  TaggedValueToFixed(secondValue);
  TaggedValueToFixed(thirdValue);
  mode = func_ov001_02063a24();
  if (mode != 0) {
    mode = func_ov001_02063a38();
  }
  else {
    mode = 0;
  }
  if (mode != 7) {
    FlushMarkerPosition(*(unsigned int *)(event + 4) & 0xffff);
  }
  return 0;
}
