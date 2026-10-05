extern int data_ov021_020b56c4[];
#define activeObject_020b56ac data_ov021_020b56c4[2]
extern unsigned int VEC_Mag();
extern unsigned int FX_Div();
extern unsigned int VEC_Subtract();
extern unsigned int BeginWalkerMove();
extern unsigned int ResolveTaggedValueRef();
extern unsigned int TaggedValueToFixed();
extern unsigned int ResolveVectorOperand();

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
  ResolveVectorOperand(context,operands,position);
  if (speed != 0) {
    VEC_Subtract(position,object + 0x2c0,delta);
    duration = VEC_Mag(delta);
    duration = FX_Div(duration,speed);
  }
  BeginWalkerMove(object,position,duration,0);
  return 0;
}
