extern int data_ov022_020b7da8[];
#define activeStream_020b7d90 data_ov022_020b7da8[2]

void ActivateSubtitleStream(void)

{
  if (activeStream_020b7d90 != 0) {
    if (*(unsigned char *)(activeStream_020b7d90 + 0x38) == '\0') {
      *(unsigned char *)(activeStream_020b7d90 + 0x38) = 1;
    }
    return;
  }
  return;
}
