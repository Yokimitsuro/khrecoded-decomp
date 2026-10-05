extern int data_ov021_020b56c4[];
#define activeObject_020b56ac data_ov021_020b56c4[2]
extern unsigned int VEC_Mag();
extern unsigned int FX_Div();
extern unsigned int VEC_Subtract();
extern unsigned int func_ov001_020910ec();
extern unsigned int ResolveTaggedValueRef();
extern unsigned int TaggedValueToFixed();
extern unsigned int func_ov021_020b03e8();

unsigned int ScriptOp_MoveObjectWithSpeed(unsigned int context,int operands)

{
  int object;
  int speed;
  unsigned int duration;
  unsigned char position [12];
  unsigned char delta [12];
  
  speed = ResolveTaggedValueRef(context,operands + 8);
  object = activeObject_020b56ac;
  speed = TaggedValueToFixed(speed);
  duration = 0xffffffff;
  func_ov021_020b03e8(context,operands,position);
  if (speed != 0) {
    VEC_Subtract(position,object + 0x2c0,delta);
    duration = VEC_Mag(delta);
    duration = FX_Div(duration,speed);
  }
  func_ov001_020910ec(object,position,duration,0);
  return 0;
}
