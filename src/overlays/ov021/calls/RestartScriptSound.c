#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x14];
    u32 (*play)(int kind, void *arc, int soundId, int arg);
    u8 pad_18[4];
    s8 kind;
    u8 pad_1D[7];
    u32 *handle;
    u8 pad_28[0xc];
    void *arc;
    u32 handleValue;
} ScriptSound;

extern void StopSoundSeqHandle(u32 handle);

BOOL RestartScriptSound(ScriptSound *sound, int soundId) {
    if (sound->handle != NULL) {
        StopSoundSeqHandle(*sound->handle);
    }
    sound->handleValue = sound->play(sound->kind, sound->arc, soundId, 0);
    sound->handle = &sound->handleValue;
    return TRUE;
}
