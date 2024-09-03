#define Uses_TScreen
#include <tvision/tv.h>

#include <internal/termdisp.h>
#include <internal/linuxcon.h>
#include <internal/getenv.h>
//
#if !defined( __BORLANDC__ )
#include <string_view>
#endif

namespace tvision
{

TermCap TerminalDisplay::getCapabilities() noexcept
{
    TermCap termcap {};

    bool termXterm = false;

#if !defined(TV_BARE_METAL)

    // Allow env var detection if not a bare metal

#if defined( __BORLANDC__ )
    // TStringView is only for BCC
    auto colorterm = getEnv<TStringView>("COLORTERM");
    if (colorterm == "truecolor" || colorterm == "24bit")
    {
        termcap.colors = Direct;
    }
#else
    // Use normal std::string_view
    // TERM in Debian displays "xterm-256color"
    // COLORTERM in Debian is empty

    // Changing detection of terminal capabilities by environment vars
    auto termStr      = getEnv<std::string_view>("TERM");
    auto colortermStr = getEnv<std::string_view>("COLORTERM");

    bool term256c  = false;
    bool term24bit = false;
    if (!termStr.empty())
    {
        auto pos = termStr.find("xterm", 0);
        if (pos==0)
        {
            // found at start
            termXterm = true;
        }
    
        pos = termStr.find("256color", 0);
        if (pos!=termStr.npos)
        {
            term256c = true;
        }

        pos = termStr.find("truecolor", 0);
        if (pos!=termStr.npos)
        {
            term24bit = true;
        }

        pos = termStr.find("24bit", 0);
        if (pos!=termStr.npos)
        {
            term24bit = true;
        }
    }

    if (!colortermStr.empty())
    {
        auto pos = termStr.find("256color", 0);
        if (pos!=termStr.npos)
        {
            term256c = true;
        }

        pos = termStr.find("truecolor", 0);
        if (pos!=termStr.npos)
        {
            term24bit = true;
        }
    
        pos = termStr.find("24bit", 0);
        if (pos!=termStr.npos)
        {
            term24bit = true;
        }
    
    }


    if (term256c)
    {
        termcap.colors = Indexed256;
    }
    else if (term24bit)
    {
        termcap.colors = Direct;
    }
#endif

    else

#endif // !defined(TV_BARE_METAL)

    // Common term capabilities detection
    {
        int colors = getColorCount();
        if (colors >= 256*256*256)
            termcap.colors = Direct;
        else if (colors >= 256)
            termcap.colors = Indexed256;
        else if (colors >= 16)
            termcap.colors = Indexed16;
        else if (colors >= 8)
        {
            termcap.colors = Indexed8;
            termcap.quirks |= qfBoldIsBright;
#if !defined(TV_BARE_METAL)
#ifdef __linux__
            if (io.isLinuxConsole())
                termcap.quirks |= qfBlinkIsBright | qfNoItalic | qfNoUnderline;
            else
#endif // __linux__
#endif // !defined(TV_BARE_METAL)
            //if (getEnv<TStringView>("TERM") == "xterm")
            if (termXterm)
                // Let's assume all terminals disguising themselves as 'xterm'
                // support at least 16 colors.
                termcap.colors = Indexed16;
        }
    }
    return termcap;
}

ushort TerminalDisplay::getScreenMode() noexcept
{
    ushort mode;
    if (termcap.colors == NoColor)
        mode = TDisplay::smMono;
    else
        mode = TDisplay::smCO80;

    if (termcap.colors == Direct)
        mode |= TDisplay::smColor256 | TDisplay::smColorHigh;
    else if (termcap.colors == Indexed256)
        mode |= TDisplay::smColor256;

    TPoint fontSize = io.getFontSize();
    if (fontSize.x > 0 && fontSize.y > 0 && fontSize.x >= fontSize.y)
        mode |= TDisplay::smFont8x8;

    return mode;
}

bool TerminalDisplay::screenChanged() noexcept
{
    TPoint size = io.getSize();
    bool changed = (size != lastSize);
    lastSize = size;
    return changed;
}

} // namespace tvision
