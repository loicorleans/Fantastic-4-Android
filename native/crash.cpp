// A fatal signal in the game or the host is written to the log before Android takes the process: the signal, the
// address it faulted on, and the call chain with each frame's library and offset, to read the crash from the log
// alone. Installed once from main().
#include <dlfcn.h>
#include <signal.h>
#include <ucontext.h>
#include <unistd.h>
#include <unwind.h>

#include <atomic>
#include <cstdint>

#include "core/log.h"

namespace {

struct Walk {
    int n = 0;
};

void LogFrame(int i, uintptr_t pc) {
    Dl_info info{};
    if (pc && dladdr(reinterpret_cast<void*>(pc), &info) && info.dli_fname) {
        uintptr_t base = reinterpret_cast<uintptr_t>(info.dli_fbase);
        if (info.dli_sname) {
            uintptr_t sym = reinterpret_cast<uintptr_t>(info.dli_saddr);
            LOGE("  #%02d %s+0x%zx (%s+0x%zx)", i, info.dli_sname, size_t(pc - sym), info.dli_fname, size_t(pc - base));
        } else {
            LOGE("  #%02d %s+0x%zx", i, info.dli_fname, size_t(pc - base));
        }
    } else {
        LOGE("  #%02d 0x%zx", i, size_t(pc));
    }
}

_Unwind_Reason_Code Step(_Unwind_Context* ctx, void* arg) {
    Walk* w = static_cast<Walk*>(arg);
    uintptr_t pc = _Unwind_GetIP(ctx);
    if (pc) LogFrame(w->n++, pc);
    return w->n >= 40 ? _URC_END_OF_STACK : _URC_NO_REASON;
}

void Handler(int sig, siginfo_t* si, void* uctx) {
    static std::atomic<bool> inside{false};
    if (inside.exchange(true)) _exit(128 + sig);
    LOGE("CRASH: signal %d (code %d), fault address %p, thread %d", sig, si ? si->si_code : 0, si ? si->si_addr : nullptr,
         int(gettid()));
#if defined(__aarch64__)
    if (auto* c = static_cast<ucontext_t*>(uctx)) {
        LOGE("  pc 0x%llx lr 0x%llx sp 0x%llx", (unsigned long long)c->uc_mcontext.pc,
             (unsigned long long)c->uc_mcontext.regs[30], (unsigned long long)c->uc_mcontext.sp);
        LogFrame(0, uintptr_t(c->uc_mcontext.pc));
        LogFrame(1, uintptr_t(c->uc_mcontext.regs[30]));
    }
#endif
    Walk w;
    _Unwind_Backtrace(Step, &w);
    logx::Flush();
    // the default action: Android's own crash report, and the process ends
    signal(sig, SIG_DFL);
    raise(sig);
}

}  // namespace

void InstallCrashHandler() {
    static char stack[64 * 1024];
    stack_t ss{};
    ss.ss_sp = stack;
    ss.ss_size = sizeof(stack);
    sigaltstack(&ss, nullptr);
    struct sigaction sa{};
    sa.sa_sigaction = Handler;
    sa.sa_flags = SA_SIGINFO | SA_ONSTACK;
    sigemptyset(&sa.sa_mask);
    for (int sig : {SIGSEGV, SIGBUS, SIGILL, SIGFPE, SIGABRT, SIGTRAP}) sigaction(sig, &sa, nullptr);
}
