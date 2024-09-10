#pragma once


namespace tvision {

#ifdef __BORLANDC__
typedef uint32_t TTimePoint;
#else
    #ifdef TV_BARE_METAL
        typedef uint32_t TTimePoint;
    #else
        typedef uint64_t TTimePoint;
    #endif
#endif


} // namespace tvision

