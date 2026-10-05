extern unsigned int data_ov021_020b5628;
extern unsigned int func_ov021_020a8830();

int GetGroupMemberData(unsigned int groupId,int index)

{
  int *group;
  
  if (data_ov021_020b5628 == 0) {
    return 0;
  }
  group = (int *)func_ov021_020a8830(groupId);
  if (group == (int *)0x0) {
    return 0;
  }
  return *group + index * 0x138 + 8;
}
