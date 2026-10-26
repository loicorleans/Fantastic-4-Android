// DSOUND exports the title's XACTENG audio engine calls that have no host version.
//
// The host owns every DirectSound object (src/sound): a buffer or stream is a host block with no voice behind it.
// The library code of these exports reads the library's own voice object (this->[0x10], then flags at voice+0xb) and
// faults on a null guest pointer. They only tune a voice (pitch, LFO, envelope, ...), which the mixer does not model,
// so each returns S_OK and pops its arguments. Found from the log of the first run: sub_0016C86A, called from
// XACTENG through sub_0016DCC7, then the whole family of the same shape in one go, so they do not crash one by one.
//
// Addresses are from this default.xbe (SHA-1 d626e8043f9f268f098a669f7e2c9aea6903b17d). Left alone on purpose:
//   0x16C332, 0x16C37C, 0x16C381  XAudioCalculatePitch / CreatePcmFormat / CreateAdpcmFormat: pure functions
//   0x16DD0B                      stream FlushEx wrapper, its body is the host's CDirectSoundStream_FlushEx
#include <atomic>
#include <cstdint>

#include "core/log.h"
#include "xdk/hle.h"

using namespace kernel;

namespace {

// the first call of each stub is logged, so a run shows which of them the game reaches
#define DS_STUB(addr, nargs, what)                                                                   \
    X86_FUNC(sub_##addr) {                                                                           \
        (void)base;                                                                                  \
        static std::atomic<bool> seen{false};                                                        \
        if (!seen.exchange(true)) LOGW("dsound: %s (%s) not modelled, skipped", what, #addr);        \
        Return(ctx, 0, nargs);                                                                       \
    }

}  // namespace

// IDirectSoundBuffer methods (this, value)
DS_STUB(0016DAC3, 2, "IDirectSoundBuffer_SetPitch")
DS_STUB(0016DADF, 2, "IDirectSoundBuffer_SetLFO")
DS_STUB(0016DAFB, 2, "IDirectSoundBuffer_SetEG")
DS_STUB(0016DBCB, 2, "IDirectSoundBuffer_Pause")  // the game itself calls this one: sounds are not paused
DS_STUB(0016DC8F, 2, "IDirectSoundBuffer export B0055")
DS_STUB(0016DCAB, 2, "IDirectSoundBuffer internal wrapper")
DS_STUB(0016DCC7, 2, "IDirectSoundBuffer internal wrapper")  // the one of the first crash

// IDirectSoundStream methods (this, value)
DS_STUB(0016DCE8, 2, "IDirectSoundStream export B0099")
DS_STUB(0016DCED, 2, "IDirectSoundStream export B0092")
DS_STUB(0016DCF2, 2, "IDirectSoundStream_SetEG")
DS_STUB(0016DD23, 2, "IDirectSoundStream export B0081")
DS_STUB(0016DD28, 2, "IDirectSoundStream internal wrapper")
DS_STUB(0016DD2D, 2, "IDirectSoundStream internal wrapper")
DS_STUB(0016DD32, 0, "IDirectSoundStream internal thunk")
DS_STUB(0016E4F6, 2, "IDirectSoundStream export B0098")

// 0x16EB60: two arguments, reads 64-bit flag pairs through them; nothing in the host depends on it
DS_STUB(0016EB60, 2, "DSOUND internal 0x16EB60")

// IDirectSound_CreateSoundStream (B003B): (this, DSSTREAMDESC*, IDirectSoundStream**, outer). The host makes streams in
// DirectSoundCreateStream (0x16F4DD), which takes the same description and out pointer.
X86_FUNC(sub_0016F2AC) {
    (void)base;
    uint32_t desc = R32(ctx.esp + 8);
    uint32_t out = R32(ctx.esp + 12);
    uint32_t r = CallGuest(ctx, 0x16F4DD, {desc, out});
    Return(ctx, r, 4);
}
