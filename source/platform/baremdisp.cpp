#if defined(TV_BARE_METAL)

#define Uses_TEvent
#define Uses_TKeys
#define Uses_THardwareInfo
#include <tvision/tv.h>
#include <internal/stdioctl.h>
#include <internal/ansidisp.h>
#include <internal/terminal.h>

//
#include <internal/baremdisp.h>


#if defined(__GNUC__)
    #define ATTRIBUTE_WEAK    __attribute__((weak))
#else
    #define ATTRIBUTE_WEAK
#endif


#if !defined(TV_BARE_METAL_DISPLAY_SIZE_WIDTH)
    #ifdef TV_BARE_METAL_DISPLAY_SIZE_80_25
        #define TV_BARE_METAL_DISPLAY_SIZE_WIDTH     80
    #endif
    #ifdef TV_BARE_METAL_DISPLAY_SIZE_132_40
        #define TV_BARE_METAL_DISPLAY_SIZE_WIDTH    132
    #endif
#endif

#if !defined(TV_BARE_METAL_DISPLAY_SIZE_WIDTH)
    #define TV_BARE_METAL_DISPLAY_SIZE_WIDTH         80
#endif


#if !defined(TV_BARE_METAL_DISPLAY_SIZE_HEIGHT)
    #ifdef TV_BARE_METAL_DISPLAY_SIZE_80_25
        #define TV_BARE_METAL_DISPLAY_SIZE_HEIGHT    25
    #endif
    #ifdef TV_BARE_METAL_DISPLAY_SIZE_132_40
        #define TV_BARE_METAL_DISPLAY_SIZE_HEIGHT    40
    #endif
#endif

#if !defined(TV_BARE_METAL_DISPLAY_SIZE_HEIGHT)
    #define TV_BARE_METAL_DISPLAY_SIZE_HEIGHT        25
#endif


namespace tvision {

// TV_BARE_METAL_DISPLAY_method_name_IMPL_DISABLE


//----------------------------------------------------------------------------
#ifndef TV_BARE_METAL_DISPLAY_RELOADSCREENINFO_IMPL_DISABLE
ATTRIBUTE_WEAK
void BareMetalDisplay::reloadScreenInfo() noexcept
{
    size.x = TV_BARE_METAL_DISPLAY_SIZE_WIDTH;
    size.y = TV_BARE_METAL_DISPLAY_SIZE_HEIGHT;
}
#endif

//----------------------------------------------------------------------------
#ifndef TV_BARE_METAL_DISPLAY_GETSCREENSIZE_IMPL_DISABLE
ATTRIBUTE_WEAK
TPoint BareMetalDisplay::getScreenSize() noexcept
{
    return size;
}
#endif

//----------------------------------------------------------------------------
#ifndef TV_BARE_METAL_DISPLAY_GETCARETSIZE_IMPL_DISABLE
int BareMetalDisplay::getCaretSize() noexcept
{
    return 100;
}
#endif

//----------------------------------------------------------------------------
#ifndef TV_BARE_METAL_DISPLAY_GETCOLORCOUNT_IMPL_DISABLE
int BareMetalDisplay::getColorCount() noexcept
{
    #if defined(TV_BARE_METAL_DISPLAY_COLORS_TRUE_COLOR)
        return 256*256*256;
    #elif defined(TV_BARE_METAL_DISPLAY_COLORS_256_COLORS)
        return 256;
    #elif defined(TV_BARE_METAL_DISPLAY_COLORS_8_COLORS)
        return 8;
    #else // Assume that display has 16 colors by default
        return 16;
    #endif
}
#endif

//----------------------------------------------------------------------------
#ifndef TV_BARE_METAL_DISPLAY_CLEARSCREEN_IMPL_DISABLE
void BareMetalDisplay::clearScreen() noexcept
{
    // do nothing
}
#endif

//----------------------------------------------------------------------------
#ifndef TV_BARE_METAL_DISPLAY_SCREENCHANGED_IMPL_DISABLE
bool BareMetalDisplay::screenChanged() noexcept
{
    return false;
}
#endif

//----------------------------------------------------------------------------
#ifndef TV_BARE_METAL_DISPLAY_LOWLEVELWRITECHARS_IMPL_DISABLE
void BareMetalDisplay::lowlevelWriteChars(TStringView  /* chars */ , TColorAttr  /* attr */ ) noexcept
{
}
#endif

//----------------------------------------------------------------------------
#ifndef TV_BARE_METAL_DISPLAY_LOWLEVELMOVECURSOR_IMPL_DISABLE
void BareMetalDisplay::lowlevelMoveCursor(uint  /* x */ , uint  /* y */ ) noexcept
{
}
#endif

//----------------------------------------------------------------------------
#ifndef TV_BARE_METAL_DISPLAY_LOWLEVELCURSORSIZE_IMPL_DISABLE
void BareMetalDisplay::lowlevelCursorSize(int  /* size */ ) noexcept
{
}
#endif

//----------------------------------------------------------------------------
#ifndef TV_BARE_METAL_DISPLAY_LOWLEVELFLUSH_IMPL_DISABLE
void BareMetalDisplay::lowlevelFlush() noexcept
{
}
#endif

//----------------------------------------------------------------------------
#ifndef TV_BARE_METAL_DISPLAY_method_name_IMPL_DISABLE
#endif



} // namespace tvision


#endif // TV_BARE_METAL

