#pragma once

#ifndef Uses_THardwareInfo
    #define Uses_THardwareInfo
#endif

#include "platform.h"
//
#include "../hardware.h"
#include "../system.h"

//
#include "../umba/ansiterm/seqparser.h"
#include "../umba/ansiterm/util.h"

//
#include <deque>

// static uint32_t THardwareInfo::getTickCount() noexcept;


// class InputStrategy : public EventSource
// {
// public:
//  
//     InputStrategy(SysHandle aHandle) noexcept :
//         EventSource(aHandle)
//     {
//     }
//  
//     virtual ~InputStrategy() {}
//  
//     virtual int getButtonCount() noexcept { return 0; }
//     virtual void cursorOn() noexcept {}
//     virtual void cursorOff() noexcept {}
// };


// class Win32Input final : public InputStrategy
// {
//     StdioCtl &io;
//     InputState state;
//  
//     bool getEvent(const INPUT_RECORD &, TEvent &ev) noexcept;
//     bool getMouseEvent(MOUSE_EVENT_RECORD, TEvent &ev) noexcept;
//  
// public:
//  
//     // The lifetime of 'aIo' must exceed that of 'this'.
//     Win32Input(StdioCtl &aIo) noexcept :
//         InputStrategy(aIo.in()),
//         io(aIo)
//     {
//     }
//  
//     bool getEvent(TEvent &ev) noexcept override;
//     int getButtonCount() noexcept override;
//     void cursorOn() noexcept override;
//     void cursorOff() noexcept override;
// };


namespace tvision {




class AnsiTerminalInput : public InputStrategy
{
    StdioCtl &io;

    struct KeyInfo
    {
        ushort keyCode;
        ushort controlKeyState;
    };

    static std::deque<KeyInfo> keysDeque;

    static
    void onKeyData(ushort keyCode, ushort controlKeyState)
    {
        //TODO: !!! Dirty. Need to lock queue
        keysDeque.emplace_back(KeyInfo{keyCode, controlKeyState});
    }

    static
    void onInvalidData(const uchar*  /* pData */ , size_t  /* size */ )
    {
    }

    using Parser = umba::ansiterm::AnsiTerminalKeySequenceParser< void(*)(ushort, ushort), void(*)(const uchar*, size_t) >;


    Parser     parser;
    uint32_t   lastReadTick = 0;


    //uint32_t THardwareInfo::getTickCount() noexcept;


public:

    AnsiTerminalInput(StdioCtl &aIo) noexcept :
        InputStrategy((SysHandle)-1),
        io(aIo),
        parser(onKeyData,onInvalidData)
    {
    }

    void pollInput()
    {
        //auto curReadTick = THardwareInfo::getTickCount();
        //if ()
        //void putData(const uchar* pData, size_t size)
        //void putTimeout()

        char    buf[32];
        size_t  nReaded = 0;

        io.read(&buf[0], 32, &nReaded);

        if (!nReaded)
             return;
        
        auto curReadTick = THardwareInfo::getTickCount();
        auto deltaTick   = curReadTick - lastReadTick;
        lastReadTick     = curReadTick;

        if (deltaTick>10)
            parser.putTimeout();

        parser.putData((const uchar*)&buf[0], nReaded);
    }



    // from EventSource
    virtual bool hasPendingEvents() noexcept override
    {
        //TODO: !!! Dirty. Need to lock queue
        return !keysDeque.empty();
    }

protected:

    static
    char getKeyText(ushort keyCode, ushort controlKeyState)
    {
        bool hasAlt = (controlKeyState&(kbRightAlt|kbLeftAlt))!=0;

        if (hasAlt)
            return 0;

        const auto &constNames = umba::ansiterm::getAnsiTermKeyConstNames();

        for(auto i=0u; i!=constNames.size(); ++i)
        {
            if (constNames[i].value==keyCode)
                return 0;
        }

        ushort scanCode = (keyCode>>8) & 0xFF;
        ushort charCode = (keyCode   ) & 0xFF;
         
        const auto &taCharInfoVec = umba::ansiterm::getTerminalAsciiCharInfo();
         
        if (charCode>=0x20 && charCode<0x7F && taCharInfoVec[charCode].scanCode==scanCode)
        {
            return (char)charCode;
        }

        return 0;
    }

public:

    virtual bool getEvent(TEvent &ev) noexcept override
    {
        if (keysDeque.empty())
            return false;

        //TODO: !!! Dirty. Need to lock queue

        KeyInfo ki = keysDeque.front();
        keysDeque.pop_front();

        ev.what = evKeyDown;

        ev.keyDown.keyCode         = ki.keyCode;
        ev.keyDown.controlKeyState = ki.controlKeyState;

        ev.keyDown.text[0]    = getKeyText(ki.keyCode, ki.controlKeyState);
        ev.keyDown.textLength = (ev.keyDown.text[0]==0) ? 0 : 1;

        return true;
    }


    // from InputStrategy
    int getButtonCount() noexcept override
    {
        return 0;
    }

    void cursorOn() noexcept override
    {
    }

    void cursorOff() noexcept override
    {
    }

}; // class AnsiTerminalInput



} // namespace tvision

