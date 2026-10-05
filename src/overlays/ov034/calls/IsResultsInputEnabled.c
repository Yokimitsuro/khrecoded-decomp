#include "nitro/types.h"

#define false 0
#define true 1
extern int data_ov034_020c0fa0[2];
#define resultsWork data_ov034_020c0fa0[1]

BOOL IsResultsInputEnabled(void)

{
  if (resultsWork == 0) {
    return false;
  }
  return (*(u16 *)(resultsWork + 6) & 1) == 0;
}
