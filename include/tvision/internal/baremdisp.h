#ifndef TVISION_TERMDISP_H
#define TVISION_TERMDISP_H

#include <tvision/tv.h>
#include <compat/windows/windows.h>
#include <internal/stdioctl.h>
#include <internal/termdisp.h>


namespace tvision
{

class BareMetalDisplay : public TerminalDisplay
{

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

#endif // TVISION_TERMDISP_H
