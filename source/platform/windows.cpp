#ifndef _WIN32

#include <windows.h>

#ifndef TV_BARE_METAL
    #include <chrono>
#else
    namespace tvision {
    namespace bmtv { // BareMetal TurboVision
        uint32_t getTickCount(); // User must implement this. Tick count must be in milliseconds
    } // namespace bmtv
    } // namespace tvision
#endif


extern "C" DWORD GetTickCount() noexcept
{
    #ifndef TV_BARE_METAL
        return (DWORD) GetTickCount64();
    #else
        return tvision::bmtv::getTickCount();
    #endif
}

#ifndef TV_BARE_METAL
extern "C" ULONGLONG GetTickCount64() noexcept
{
    // This effectively gives a system time reference in milliseconds.
    // steady_clock is best suited for measuring intervals.
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now().time_since_epoch()
    ).count();
}
#endif

#endif // _WIN32
