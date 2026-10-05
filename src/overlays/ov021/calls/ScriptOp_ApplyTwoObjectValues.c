extern unsigned int data_ov021_020b56c4[];
#define activeObject_020b56ac data_ov021_020b56c4[2]
extern unsigned int TurnActorFacingDegrees();
extern unsigned int ResolveTaggedValueRef();
extern unsigned int TaggedValueToFixed();

unsigned int ScriptOp_ApplyTwoObjectValues(unsigned int context,int operands)

{
  unsigned int object;
  unsigned int firstValue;
  unsigned int secondValue;
  
  object = activeObject_020b56ac;
  firstValue = ResolveTaggedValueRef(context,operands);
  secondValue = ResolveTaggedValueRef(context,operands + 8);
  firstValue = TaggedValueToFixed(firstValue);
  secondValue = TaggedValueToFixed(secondValue);
  TurnActorFacingDegrees(object,firstValue,secondValue);
  return 0;
}
