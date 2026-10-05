extern unsigned int data_ov021_020b56c4[];
#define activeObject_020b56ac data_ov021_020b56c4[2]
extern unsigned int SetActorMotionFlag();
extern unsigned int ResolveTaggedValueRef();
extern unsigned int TaggedValueToFixed();

unsigned int ScriptOp_SetActiveObjectValue(unsigned int context, unsigned int operands)

{
  unsigned int object;
  unsigned int value;
  
  value = ResolveTaggedValueRef(context,operands);
  object = activeObject_020b56ac;
  value = TaggedValueToFixed(value);
  SetActorMotionFlag(object,value);
  return 0;
}
