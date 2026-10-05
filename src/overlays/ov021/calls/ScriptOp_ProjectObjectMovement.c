extern int data_ov021_020b56c4[];
#define activeObject_020b56ac data_ov021_020b56c4[2]
extern unsigned int VEC_MultAdd();
extern unsigned int func_ov021_020afd48();
extern unsigned int ResolveTaggedValueRef();
extern unsigned int TaggedValueToFixed();

unsigned int ScriptOp_ProjectObjectMovement(int context,int operands,unsigned int argument,unsigned int savedArgument)

{
  unsigned int scale;
  int object;
  unsigned char normal [12];
  unsigned char correction [12];
  unsigned int saved;
  
  saved = savedArgument;
  scale = ResolveTaggedValueRef(context,operands + 8);
  object = activeObject_020b56ac;
  scale = TaggedValueToFixed(scale);
  VEC_MultAdd(scale,object + 0x38c,object + 0x2c0,context + 0x34);
  object = func_ov021_020afd48(object + 0x2c0,object + 0x38c,normal,correction,0);
  if (object != 0) {
    VEC_MultAdd(0x19a,normal,context + 0x34,context + 0x34);
  }
  return 0;
}
