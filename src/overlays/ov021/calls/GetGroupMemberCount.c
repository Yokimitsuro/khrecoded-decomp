extern unsigned int data_ov021_020b5628;
extern unsigned int func_ov021_020a8830();

unsigned int GetGroupMemberCount(int groupId)

{
  int group;
  unsigned int count;
  
  count = 0;
  if (data_ov021_020b5628 == 0) {
    return 0;
  }
  group = func_ov021_020a8830(groupId);
  if (group != 0) {
    count = *(unsigned int *)(group + 4);
  }
  return count;
}
