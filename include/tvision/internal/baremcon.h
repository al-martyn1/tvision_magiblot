#pragma once

#include <internal/platform.h>
//
#include "baremdisp.h"
#include "ansiterminput.h"

namespace tvision{

class DisplayBuffer;

class BareMetalConsoleStrategy : public ConsoleStrategy
{
    DisplayBuffer &displayBuf;

    // StdioCtl &io;
    // DisplayBuffer &displayBuf;
    // InputState &inputState;
    // SigwinchHandler *sigwinch;

    BareMetalConsoleStrategy( DisplayStrategy &aDisplay, InputStrategy &aInput, StdioCtl & /* aIo */ , DisplayBuffer &aDisplayBuf) noexcept
    : ConsoleStrategy(aDisplay, aInput, {&aInput})
    , displayBuf(aDisplayBuf)
    {
    }

public:

    // The lifetime of 'io' and 'displayBuf' must exceed that of the returned object.
    // Takes ownership over 'inputState', 'display' and 'input'.
    static BareMetalConsoleStrategy &create( StdioCtl &io,
                                        DisplayBuffer &displayBuf,
                                        DisplayStrategy &display,
                                        InputStrategy &input ) noexcept
    {
        return * new BareMetalConsoleStrategy(display, input, io, displayBuf);
    }

    ~BareMetalConsoleStrategy()
    {
        delete &input;
        delete &display;
        //delete &inputState;
    }

    bool isAlive() noexcept override
    {
        input.pollInput();
        return true;
    }

    bool setClipboardText(TStringView) noexcept override
    {
        return false;
    }

    bool requestClipboardText(void (&)(TStringView)) noexcept override
    {
        return false;
    }

    static int charWidth(uint32_t) noexcept;

}; // class BareMetalConsoleStrategy



} // namespace tvision

