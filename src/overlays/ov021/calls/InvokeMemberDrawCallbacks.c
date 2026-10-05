typedef void code();


void InvokeMemberDrawCallbacks(int *container)

{
  int entry;
  code *callback;
  int index;
  
  if ((0 < container[1]) && (index = 0, 0 < container[1])) {
    do {
      entry = *(int *)(*container + index * 4);
      if ((entry != 0) && (callback = *(code **)(entry + 0x28), callback != (code *)0x0)) {
        (*callback)(container,entry);
      }
      index = index + 1;
    } while (index < container[1]);
  }
  return;
}
