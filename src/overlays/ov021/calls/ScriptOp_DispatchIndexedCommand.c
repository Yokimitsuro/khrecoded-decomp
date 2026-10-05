#include "nitro/types.h"

typedef void CommandHandler();

extern u32 gScriptQueryHandlers;
extern u32 ResolveTaggedValueRef();

u32 ScriptOp_DispatchIndexedCommand(int context,u32 operands)

{
  int commandOperand;
  
  commandOperand = ResolveTaggedValueRef(context,operands);
  *(u16 *)(context + 0x2c) = 1;
  *(u32 *)(context + 0x30) = 0;
  if (*(CommandHandler **)((u8 *)&gScriptQueryHandlers + *(int *)(commandOperand + 4) * 4) != (CommandHandler *)0x0) {
    (**(CommandHandler **)((u8 *)&gScriptQueryHandlers + *(int *)(commandOperand + 4) * 4))(context,operands);
  }
  return 0;
}
