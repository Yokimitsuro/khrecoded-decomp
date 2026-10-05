#include "nitro/types.h"

extern unsigned int gSoundWork;
extern unsigned int NNS_SndArcStrmStartPrepared();

unsigned int func_0204de64(int streamIndex) {
  if (*(unsigned char *)(gSoundWork + streamIndex * 8 + 0xb44ce) == '\x02') {
    NNS_SndArcStrmStartPrepared((void *)(gSoundWork + 0xb44c0 + streamIndex * 4));
    return 1;
  }
  return 0;
}
