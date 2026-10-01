typedef unsigned long u32;

#define ENC_VAL_1 0x1000
#define ADDR_PLUS_ADDEND(ref, addend) ((u32)(&ref + ((addend) / sizeof(ref))))

#define DSP_OBFS_OFFSET 0x320
#define FUNC_QUEUE_END 0

#define PRIME_TRUE 251
#define PRIME_FALSE 241
#define PRIME_DSPROT_MAIN 53

typedef u32 (*DSProtTask)(void);
typedef u32 (*DSProtCallback)(void *);

enum DSProtExpectedResult {
    DSPROT_EXPECT_FALSE,
    DSPROT_EXPECT_TRUE
};

extern u32 RunEncrypted_ROMTest_IsBad(void);
extern u32 RunEncrypted_ROMTest_IsGood(void);
extern u32 RunEncrypted_Integrity_ROMTest_IsBad(void);
extern u32 RunEncrypted_Integrity_ROMTest_IsGood(void);
extern u32 RunEncrypted_MACOwner_IsBad(void);
extern u32 RunEncrypted_MACOwner_IsGood(void);
extern u32 RunEncrypted_Integrity_MACOwner_IsBad(void);
extern u32 RunEncrypted_Integrity_MACOwner_IsGood(void);
extern u32 RunEncrypted_Dummy_IsBad(void);
extern u32 RunEncrypted_Dummy_IsGood(void);

static inline u32 dsprotMain(u32 *func_queue, int expected_result, void *callback, void *param) {
    u32 result;

    result = PRIME_DSPROT_MAIN * PRIME_TRUE * PRIME_FALSE;
    do {
        result += ((DSProtTask)(*func_queue - ENC_VAL_1 - DSP_OBFS_OFFSET))();
        func_queue++;
    } while (*func_queue != FUNC_QUEUE_END);

    if (expected_result == DSPROT_EXPECT_TRUE) {
        if (!(result % PRIME_TRUE)) {
            return ((DSProtCallback)callback)(param);
        }
    } else {
        if (result % PRIME_FALSE) {
            return ((DSProtCallback)callback)(param);
        }
    }

    return result;
}
