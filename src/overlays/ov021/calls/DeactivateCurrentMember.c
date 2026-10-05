typedef void code();
extern unsigned int GetBoundedEntryField();
extern unsigned int SetFieldAt0x30();

void DeactivateCurrentMember(int container)

{
  int owner;
  code *callback;
  
  if (*(int *)(container + 8) != 0) {
    callback = *(code **)(*(int *)(container + 8) + 0x2c);
    if (callback != (code *)0x0) {
      (*callback)(container,*(int *)(container + 8));
    }
    owner = GetBoundedEntryField(*(unsigned int *)(container + 0x14));
    SetFieldAt0x30(owner + 0xb2c,0xffffffff);
    *(unsigned int *)(container + 8) = 0;
  }
  return;
}
