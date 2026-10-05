extern unsigned int VEC_MultAdd();
extern unsigned int BeginWalkerMove();
extern unsigned int ResolveStageActorRef();
extern unsigned int ResolveTaggedValueRef();
extern unsigned int TaggedValueToFixed();
extern unsigned int ResolveVectorOperand();

unsigned int
ScriptOp_ApplyScaledObjectVector(unsigned int context,int operands,unsigned int argument,unsigned int savedArgument)

{
  int object;
  unsigned int scale;
  unsigned int firstValue;
  unsigned int secondValue;
  unsigned char inputVector [12];
  unsigned char resultVector [12];
  unsigned int saved;
  
  saved = savedArgument;
  object = ResolveTaggedValueRef(context,operands);
  scale = ResolveTaggedValueRef(context,operands + 0x10);
  firstValue = ResolveTaggedValueRef(context,operands + 0x18);
  secondValue = ResolveTaggedValueRef(context,operands + 0x20);
  object = ResolveStageActorRef(context,*(unsigned int *)(object + 4));
  if (object != 0) {
    ResolveVectorOperand(context,operands + 8,inputVector);
    scale = TaggedValueToFixed(scale);
    VEC_MultAdd(scale,inputVector,object + 0x2c0,resultVector);
    scale = TaggedValueToFixed(firstValue);
    firstValue = TaggedValueToFixed(secondValue);
    BeginWalkerMove(object,resultVector,scale,firstValue);
  }
  return 0;
}
