#ifndef TVISION_BAREMDISP_H
#define TVISION_BAREMDISP_H

#include <tvision/tv.h>
#include <internal/stdioctl.h>
#include <internal/termdisp.h>


namespace tvision
{

class BareMetalDisplay : public TerminalDisplay
{
    TPoint size {};

    void initCapabilities() noexcept
    {
        termcap = getCapabilities();
    }

    TermCap getCapabilities() noexcept
    {
        TermCap termcap {};
    
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
        }
        
        return termcap;
    }

public:

    // The lifetime of 'aIo' must exceed that of 'this'.
    BareMetalDisplay(StdioCtl &aIo) noexcept :
        TerminalDisplay(aIo)
    {
        initCapabilities();
    }

    void reloadScreenInfo() noexcept override;
    TPoint getScreenSize() noexcept override;
    int getCaretSize() noexcept override;
    int getColorCount() noexcept override;
    void clearScreen() noexcept override;
    bool screenChanged() noexcept override;

protected:

    void lowlevelWriteChars(TStringView chars, TColorAttr attr) noexcept override;
    void lowlevelMoveCursor(uint x, uint y) noexcept override;
    void lowlevelCursorSize(int size) noexcept override;
    void lowlevelFlush() noexcept override;
};



} // namespace tvision

#endif // TVISION_BAREMDISP_H
