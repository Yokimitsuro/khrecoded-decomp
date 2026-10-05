#include "nitro/types.h"

extern u32 ResolveTaggedValueRef();
extern u32 TaggedValueToFixed();

u32 AddScriptContextVector(void *context,int operands)

{
  void *xOperand;
  void *yOperand;
  void *zOperand;
  int component;
  
  xOperand = ResolveTaggedValueRef(context,(void *)(operands + 8));
  yOperand = ResolveTaggedValueRef(context,(void *)(operands + 0x10));
  zOperand = ResolveTaggedValueRef(context,(void *)(operands + 0x18));
  component = TaggedValueToFixed(xOperand);
  *(int *)((int)context + 0x34) = *(int *)((int)context + 0x34) + component;
  component = TaggedValueToFixed(yOperand);
  *(int *)((int)context + 0x38) = *(int *)((int)context + 0x38) + component;
  component = TaggedValueToFixed(zOperand);
  *(int *)((int)context + 0x3c) = *(int *)((int)context + 0x3c) + component;
  return 0;
}
