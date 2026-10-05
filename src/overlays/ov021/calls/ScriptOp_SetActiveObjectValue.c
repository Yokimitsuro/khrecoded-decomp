extern unsigned int data_ov021_020b56c4[];
#define activeObject_020b56ac data_ov021_020b56c4[2]
extern unsigned int func_ov001_020911b4();
extern unsigned int ResolveTaggedValueRef();
extern unsigned int TaggedValueToFixed();

unsigned int ScriptOp_SetActiveObjectValue(unsigned int context, unsigned int operands)

{
  unsigned int object;
  unsigned int value;
  
  value = ResolveTaggedValueRef(context,operands);
  object = activeObject_020b56ac;
  value = TaggedValueToFixed(value);
  func_ov001_020911b4(object,value);
  return 0;
}
