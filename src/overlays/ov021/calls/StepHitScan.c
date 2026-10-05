#include "nitro/types.h"

typedef struct {
    u32 data[0x35];
} HitResult;

typedef struct {
    HitResult result;
    int state;
    void *pending;
} HitScan;

typedef struct {
    u8 pad_00[0x24];
    u16 flagsLow : 10;
    u16 skipContacts : 1;
    u16 flag11 : 1;
    u16 skipNearest : 1;
    u16 flagsHigh : 3;
} HitOptions;

extern BOOL IsFirstEntryFlagSet(void);
extern void func_ov021_020ac168(HitScan *scan);
extern void *func_ov001_0207f0b4(void);
extern void *func_ov001_02087264(void);
extern void ForwardToActiveService(void);
extern BOOL func_ov021_020ab950(int type, void *attack, HitOptions *options, HitScan *scan);
extern BOOL ResolveNearestHitNode(int type, void *attack, HitOptions *options, HitScan *scan);
extern BOOL ResolveHitContacts(int type, void *attack, HitOptions *options, HitScan *scan);
extern void func_ov021_020abe74(int type, void *attack, HitOptions *options, HitScan *scan);

BOOL StepHitScan(int type, void *attack, HitOptions *options, HitScan *scan) {
    BOOL proceed;
    if (IsFirstEntryFlagSet()) {
        return FALSE;
    }
    if (scan->state >= 8) {
        return FALSE;
    }
    func_ov021_020ac168(scan);
    switch (scan->state) {
    case 1:
        scan->pending = func_ov001_0207f0b4();
        scan->state = 2;
    case 2:
        if (func_ov021_020ab950(type, attack, options, scan)) {
            proceed = TRUE;
            if (options != NULL && options->skipNearest) {
                proceed = FALSE;
            }
            if (proceed) {
                scan->state = 3;
            } else {
                scan->state = 5;
            }
        }
        break;
    case 3:
        scan->pending = func_ov001_02087264();
        scan->state = 4;
    case 4:
        if (ResolveNearestHitNode(type, attack, options, scan)) {
            scan->state = 5;
        }
        break;
    case 5:
        ForwardToActiveService();
        scan->state = 6;
    case 6:
        if (ResolveHitContacts(type, attack, options, scan)) {
            proceed = TRUE;
            if (options != NULL && options->skipContacts) {
                proceed = FALSE;
            }
            if (proceed) {
                scan->state = 7;
            } else {
                scan->state = 8;
            }
        }
        break;
    case 7:
        func_ov021_020abe74(type, attack, options, scan);
        scan->state = 8;
        break;
    }
    return TRUE;
}
