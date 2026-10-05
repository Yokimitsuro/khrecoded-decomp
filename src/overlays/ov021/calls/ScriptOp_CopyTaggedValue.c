extern unsigned int ResolveTaggedValueRef();

unsigned int ScriptOp_CopyTaggedValue(void *context,short *operands)

{
  short *source;
  short *destination;
  
  source = ResolveTaggedValueRef(context,operands + 4);
  if (*operands == 8) {
    destination = ResolveTaggedValueRef(context,operands);
    *destination = *source;
    destination[1] = 0;
    *(unsigned int *)(destination + 2) = *(unsigned int *)(source + 2);
  }
  return 0;
}
