#include "nitro/types.h"

extern struct { int reserved[2]; u32 object; } data_ov021_020b56c4;
#define currentScriptObject data_ov021_020b56c4.object
extern u32 SetLookAtTarget();
extern u32 ResolveTaggedValueRef();
extern u32 ResolveVectorOperand();

u32 ScriptOp_ApplyCurrentObjectPosition(u32 context,int operands)

{
  u32 object;
  int valueOperand;
  u8 vector [12];
  
  valueOperand = ResolveTaggedValueRef(context,operands + 8);
  object = currentScriptObject;
  ResolveVectorOperand(context,operands,vector);
  SetLookAtTarget(object,vector,*(u32 *)(valueOperand + 4));
  return 0;
}
