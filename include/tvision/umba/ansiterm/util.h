#pragma once

#include "termasciici.h"

//
#include <array>

// tvision::umba::ansiterm::
namespace tvision{
namespace umba{
namespace ansiterm{

template<typename ConstantType>
struct TConstantName
{
    ConstantType  value;
    const char   *name ;
};

#define TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(c)  { c, #c }



template<typename StreamType>
void ansiTermPrintControlKeyCode(StreamType &os, ushort controlKeyState)
{
#if !defined( __FLAT__ )
    constexpr static const size_t size = 4;
    static const ushort  flags[size] = { 0x0008, 0x0004, 0x0001     , 0x0002      };
    static const char*   names[size] = { "Alt" , "Ctrl", "LeftShift", "RightShift" };
#else
    constexpr static const size_t size = 5;
    static const ushort  flags[size] = { 0x0001    , 0x0002   , 0x0004     , 0x0008    , 0x0010    };
    static const char*   names[size] = { "RightAlt", "LeftAlt", "RightCtrl", "LeftCtrl", "Shift" };
#endif

    bool bFirst = true;
    for(auto i=0; i!=size; ++i)
    {
        if ((controlKeyState&flags[i])!=0)
        {
            if (!bFirst)
               os << "|";

            bFirst = false;
            os << "kb" << names[i];
        }
    }
}

inline
const std::array<TConstantName<ushort>, 82>& getAnsiTermKeyConstNames()
{
    static
    std::array<TConstantName<ushort>, 82> constNames =   {
    { TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbCtrlA    )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbCtrlB    )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbCtrlC    )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbCtrlD    )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbCtrlE    )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbCtrlF    )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbCtrlG    )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbBack     )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbCtrlJ    )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbCtrlK    )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbCtrlL    )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbCtrlN    )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbCtrlO    )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbCtrlP    )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbCtrlQ    )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbCtrlR    )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbCtrlS    )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbCtrlT    )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbCtrlU    )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbCtrlV    )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbCtrlW    )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbCtrlX    )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbCtrlY    )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbCtrlZ    )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbEsc      )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbAltEsc   )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbF1       )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbF2       )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbF3       )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbF4       )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbF5       )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbF6       )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbF7       )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbF8       )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbF9       )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbF10      )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbF11      )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbF12      )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbShiftF1  )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbShiftF2  )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbShiftF3  )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbShiftF4  )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbShiftF5  )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbShiftF6  )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbShiftF7  )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbShiftF8  )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbShiftF9  )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbShiftF10 )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbShiftF11 )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbShiftF12 )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbAltF1    )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbAltF2    )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbAltF3    )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbAltF4    )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbAltF5    )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbAltF6    )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbAltF7    )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbAltF8    )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbAltF9    )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbAltF10   )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbAltF11   )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbAltF12   )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbUp       )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbDown     )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbRight    )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbLeft     )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbAltUp    )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbAltDown  )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbAltRight )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbAltLeft  )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbCtrlUp   )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbCtrlDown )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbCtrlRight)
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbCtrlLeft )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbHome     )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbIns      )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbDel      )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbEnd      )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbAltHome  )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbAltIns   )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbAltDel   )
    , TVISION_UMBA_ANSITERM_DEF_CONSTANT_NAME(kbAltEnd   )
    }
    };

    return constNames;

}

template<typename StreamType>
void ansiTermPrintKeyCode(StreamType &os, ushort keyCode, ushort controlKeyState)
{

    const auto &constNames = getAnsiTermKeyConstNames();

    for(auto i=0u; i!=constNames.size(); ++i)
    {
        if (constNames[i].value==keyCode)
        {
            os << constNames[i].name;
            return;
        }
    }


    ushort scanCode = (keyCode>>8) & 0xFF;
    ushort charCode = (keyCode   ) & 0xFF;

    bool hasAlt = (controlKeyState&(kbRightAlt|kbLeftAlt))!=0;

    const auto &taCharInfoVec = getTerminalAsciiCharInfo();

    if (charCode>=0x20 && charCode<0x7F && taCharInfoVec[charCode].scanCode==scanCode)
    {
        os << "kb";
        if (hasAlt)
            os << "Alt";
        os << "_";
        if (charCode==0x20)
           os << "space";
        else
           os << (char)charCode;

        return;
    }

    os << keyCode;

}

} // namespace ansiterm{
} // namespace umba{
} // namespace tvision{ 



