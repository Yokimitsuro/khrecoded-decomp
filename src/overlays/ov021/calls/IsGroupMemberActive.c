extern unsigned int data_ov021_020b5628;
extern unsigned int func_ov021_020a8830();

unsigned int IsGroupMemberActive(unsigned int groupId,int index)

{
  int *group;
  
  if (data_ov021_020b5628 == 0) {
    return 0;
  }
  group = (int *)func_ov021_020a8830(groupId);
  if (group == (int *)0x0) {
    return 0;
  }
  if (*(char *)(*group + index * 0x138) == '\x01') {
    return 1;
  }
  return 0;
}
