extern unsigned int GetWorldMeshNamedEntry();
extern unsigned int func_ov001_020681e8();

unsigned int AnyLinkedObjectHasStateSeven(int *object)

{
  int linkedObject;
  int index;
  unsigned int result;
  
  result = 1;
  if (object[1] == 2) {
    result = 0;
    index = 0;
    do {
      linkedObject = GetWorldMeshNamedEntry(*(unsigned char *)(*object + index + 0x80));
      if ((linkedObject != 0) && (linkedObject = func_ov001_020681e8(linkedObject,7), linkedObject != 0)) {
        result = 1; break;
      }
      index = index + 1;
    } while (index < 4);
  }
  return result;
}
