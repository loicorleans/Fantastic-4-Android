// the APU's sample counter (0xFE80200C) at 48 kHz, read by the game's own XACT engine, from the host clock
#include <chrono>
#include <cstdint>

#include "cpu/x86_context.h"

static uint32_t ApuClock() {
    using namespace std::chrono;
    static const auto t0 = steady_clock::now();
    auto ns = (uint64_t)duration_cast<nanoseconds>(steady_clock::now() - t0).count();
    return (uint32_t)(ns * 48000ull / 1000000000ull);
}

// [[hook]] in config/game.toml: true makes the generated code jump over the original mov
bool ApuSampleClockEax(X86Context& ctx, uint8_t*) { ctx.eax = ApuClock(); return true; }
bool ApuSampleClockEbx(X86Context& ctx, uint8_t*) { ctx.ebx = ApuClock(); return true; }
