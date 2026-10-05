#include "nitro/types.h"

extern struct { int reserved[2]; u32 object; } data_ov021_020b56c4;
#define currentScriptObject data_ov021_020b56c4.object
extern u32 func_ov001_020910ec();
extern u32 ResolveTaggedValueRef();
extern u32 TaggedValueToFixed();
extern u32 func_ov021_020b03e8();

u32
ScriptOp_SetCurrentObjectVector(u32 context,int operands,u32 unused,u32 argument)

{
  u32 object;
  u32 firstValue;
  u32 secondValue;
  u8 vector [12];
  u32 savedArgument;
  
  object = currentScriptObject;
  savedArgument = argument;
  firstValue = ResolveTaggedValueRef(context,operands + 8);
  secondValue = ResolveTaggedValueRef(context,operands + 0x10);
  func_ov021_020b03e8(context,operands,vector);
  firstValue = TaggedValueToFixed(firstValue);
  secondValue = TaggedValueToFixed(secondValue);
  func_ov001_020910ec(object,vector,firstValue,secondValue);
  return 0;
}
